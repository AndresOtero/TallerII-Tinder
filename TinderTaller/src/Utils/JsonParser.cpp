/*
 * JsonParser.cpp
 *
 *  Created on: 16 de abr. de 2016
 *      Author: andres
 */

#include "JsonParser.h"

JsonParser::JsonParser() {
	/**Creo el parser de Json**/
}
bool JsonParser::isNullValue(Json::Value val) {
	/**Devuelve true si el value es null**/
	return val.isNull();
}
std::string JsonParser::parseBody(std::string body) {
	/**Funcion sucia para parsear el body**/
	std::queue <char> brackets;
	int i;
	for (i =0;i<body.size();i++){
		if(body[i]=='{'){
			brackets.push('{');
		}
		if(body[i]=='}'){
			brackets.pop();
		}
		if(brackets.empty()){
			break;
		}
	}
	std::string sub=body.substr(0,i+1);
	size_t size=body.size();
	return sub;
}
Json::Value JsonParser::stringToValue(std::string jsonStr) {
	/**Recibo un string y lo devuelvo con Value de Json.**/
	jsonStr=this->parseBody(jsonStr);
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(jsonStr.c_str(), root); //parse process
	if (!parsingSuccessful) {
		LOG(INFO)<< "Json: No se parseo de manera satisfactoria";
	} else {
		LOG(INFO) << "Json: Se parseo de manera satisfactoria";
	}
	return root;
}
std::string  JsonParser::valueToString(Json::Value value){
	/****/
	Json::FastWriter fastWriter;
	return fastWriter.write(value);
}
int JsonParser::getIntFromValue(Json::Value jsonValue, std::string key) {
	/**Devuelvo el valor entero que esta registrado en el value de Json con la key**/
	return jsonValue[key].asInt();
}
std::string JsonParser::getMail(std::string jsonStr){
	Json::Value val = stringToValue(jsonStr);
	return getStringFromValue(val["user"], "email");
}
std::string JsonParser::getPassword(std::string jsonStr){
	Json::Value val = stringToValue(jsonStr);
	return getStringFromValue(val["user"], "password");
}
std::string JsonParser::removePassword(Json::Value val ){
	Json::Value pass=val["user"].removeMember("password");
	return pass.asString();
}
std::string JsonParser::removeGcmId(Json::Value val ){
	Json::Value pass=val["user"].removeMember("gcm_registration_id");
	return pass.asString();
}
std::string JsonParser::getId(std::string jsonStr){
	Json::Value val = stringToValue(jsonStr);
	return getStringFromValue(val["user"], "id");
}
std::string JsonParser::getStringFromValue(Json::Value jsonValue,
		std::string key) {
	/**Devuelvo un string que esta registrado en el value de Json con la key**/
	return jsonValue[key].asString();
}
std::string JsonParser::removeMember(Json::Value val, std::string valRemove){
	Json::Value rdo = val.removeMember(valRemove);
	return rdo.asString();
}
Json::Value JsonParser::replaceNewUserInOldUser(Json::Value newVal,Json::Value oldVal){
	Json::Value oldUser=oldVal["user"];
	//oldUser.removeMember("id");
	Json::Value newUser=newVal["user"];
	for( Json::ValueIterator itr = newUser.begin() ; itr != newUser.end() ; itr++ ){
		if(oldUser.isMember(itr.key().asString())){
			LOG(INFO)<< itr.key().asString();
			LOG(INFO)<< (*itr).toStyledString();
			oldUser[itr.key().asCString()]=(*itr);
		}
	}
	oldVal["user"]=oldUser;
	oldVal["metadata"]=newVal["metadata"];
	return oldVal;
}
std::vector<std::string> JsonParser::getKeyVectorFromValue(Json::Value value){
	std::vector<std::string> keyVector;
	for( Json::ValueIterator itr = value.begin() ; itr != value.end() ; itr++ ){
		keyVector.push_back(itr.key().asString());
	}
	return keyVector;
}

JsonParser::~JsonParser() {
	/**Destruyo el parser de Json**/
}

