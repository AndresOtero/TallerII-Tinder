/*
 * TokenAuthentificator.cpp
 *
 *  Created on: 24 de abr. de 2016
 *      Author: andres
 */
#include "TokenAuthentificator.h"
using namespace std;
TokenAuthentificator::TokenAuthentificator(shared_ptr<DataBase> DB) {
	// TODO Auto-generated constructor stub
	this->DB=DB;
}
string TokenAuthentificator::createJsonTokenHeader(){
	/**Creo json Token Header**/
	Json::Value jsonHeader;
	jsonHeader["alg"] = alg;
	jsonHeader["typ"] = type;
	string strHeader=jsonParser.valueToString(jsonHeader);
	return base64Utils.base64_encodeString(strHeader);
}

string TokenAuthentificator::createJsonTokenPayload(string user, string time) {
	/**Creo json Token payload**/
	Json::Value jsonPayload;
	jsonPayload["user"] = user;
	jsonPayload["time"] = time;
	string strPayload = jsonParser.valueToString(jsonPayload);
	return base64Utils.base64_encodeString(strPayload);
}
string TokenAuthentificator::createJsonTokenSignature(string encodedHeader, string encodedPayload) {
	/**Creo json Token signature**/
	string signature =encodedHeader+"."+encodedPayload;
	string encodedKey=base64Utils.base64_encodeString(key);
	string encodedSignature=base64Utils.base64_encodeString(hmac<SHA256>(signature,encodedKey));
	return encodedSignature;
}
std::string TokenAuthentificator::createJsonToken(std::string user){
	/**Creo json Token con tiempo actual**/
	return createJsonToken(user,timeUtils.timeToString());
}

string TokenAuthentificator::createJsonToken(string user,string time){
	/**Creo json Token con tiempo pasado por parametro**/
	//https://jwt.io/introduction/
	string encodedHeader=this->createJsonTokenHeader();
	string encodedPayload=this->createJsonTokenPayload(user,time);
	string encodedSecret=this->createJsonTokenSignature(encodedHeader,encodedPayload);
	string jwt=encodedHeader+"."+encodedPayload+"."+encodedSecret;
	DBtuple tokenTuple("token_"+user,jwt);
	DB->put(tokenTuple);
	return jwt;
}

string TokenAuthentificator::getSingature(string jsonToken){
	/**Devuelvo el signature del token**/
	size_t firstDot = jsonToken.find_first_of(".");
	size_t lastDot = jsonToken.find_last_of(".");
	string strSignature= jsonToken.substr(lastDot+ 1,jsonToken.length());
	return strSignature;
}
string TokenAuthentificator::getPayloadDecoded(string jsonToken){
	/**Devuelvo el payload decoded**/
	size_t firstDot = jsonToken.find_first_of(".");
	size_t lastDot = jsonToken.find_last_of(".");
	string strPayloadEncoded = jsonToken.substr(firstDot + 1,lastDot - firstDot - 1);
	return base64Utils.base64_decode(strPayloadEncoded);
}
string TokenAuthentificator::getUserName(string jsonToken){
	/**Devuelvo el user name del token**/
	string strPayloadDecoded=this->getPayloadDecoded(jsonToken);
	Json::Value val = jsonParser.stringToValue(strPayloadDecoded);
	return jsonParser.getStringFromValue(val, "user");
}
string TokenAuthentificator::getTokenTime(string jsonToken){
	/**Devuelvo el tiempo del token**/
	string strPayloadDecoded=this->getPayloadDecoded(jsonToken);
	Json::Value val = jsonParser.stringToValue(strPayloadDecoded);
	return jsonParser.getStringFromValue(val, "time");
}

bool TokenAuthentificator::validateJsonTokenUser(string jsonToken){
	/**Valido el json Token**/
	string userName=this->getUserName(jsonToken);
	DBtuple keyTuple("token_"+userName);
	bool ok=DB->get(keyTuple);
	if(!ok){
		LOG(INFO)<<"Token: No existe el usuario en la base de datos";
		return false;
	}
	return true;
}

bool TokenAuthentificator::deleteJsonTokenUser(string jsonToken){
	/**Destruyo el json Token**/
	string userName=this->getUserName(jsonToken);
	DBtuple keyTuple("token_"+userName);
	bool ok=DB->delete_(keyTuple);
	return true;
}



bool TokenAuthentificator::validateJsonTokenSignature(string jsonToken){
	/**Valido el json Token signature**/
	string userName=this->getUserName(jsonToken);
	DBtuple keyTuple("token_"+userName);
	bool ok=DB->get(keyTuple);
	string dbToken=keyTuple.value;
	string signatureDBToken=getSingature(dbToken);
	cout<< "db  "<<signatureDBToken<<"\n";
	cout<< "db len "<<signatureDBToken.length()<<"\n";
	string signatureToken=getSingature(jsonToken);
	cout<< "to  "<<signatureToken<<"\n";
	cout<< "to len "<<signatureToken.length()<<"\n";
	if(getSingature(jsonToken)!=getSingature(dbToken)){
		LOG(INFO)<<"No esta bien el signature del token";
		return false;
	}
	return true;
}

bool TokenAuthentificator::validateJsonTokenTime(string jsonToken){
	/**Valido el json Token time **/
	string time=this->getTokenTime(jsonToken);
	double timeDifference=this->timeUtils.stringtoTimeDifferencefromNow(time);
	if(timeDifference>experationTime){
		LOG(INFO)<<"Token expirado";
		string user=this->getUserName(jsonToken);
		DBtuple key("token_"+user);
		this->DB->delete_(key);
		return false;
	}
	return true;
}

bool TokenAuthentificator::validateJsonToken(string jsonToken){
	/**Valido el json Token**/
	if(!validateJsonTokenUser(jsonToken)){
		return false;
	}
	if(!validateJsonTokenSignature(jsonToken)){
		return false;
	}
	if(!validateJsonTokenTime(jsonToken)){
		return false;
	}
	return true;
}

TokenAuthentificator::~TokenAuthentificator() {
	// destructor
}

