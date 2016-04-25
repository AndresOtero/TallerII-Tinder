/*
 * TokenAuthentificator.cpp
 *
 *  Created on: 24 de abr. de 2016
 *      Author: andres
 */
#include "TokenAuthentificator.h"
using namespace std;
TokenAuthentificator::TokenAuthentificator() {
	// TODO Auto-generated constructor stub
}

string TokenAuthentificator::createJsonToken(string user,string time){
	//https://jwt.io/introduction/

	Json::Value jsonHeader;
	jsonHeader["alg"]= "HS256";
	jsonHeader["typ"]= "JWT";
	string strHeader=jsonParser.valueToString(jsonHeader);
	Json::Value jsonPayload;
	jsonPayload["user"]=user;
	jsonPayload["time"]=time;
	string strPayload=jsonParser.valueToString(jsonPayload);
	string encodedHeader=base64Utils.base64_encodeString(strHeader);
	string encodedPayload=base64Utils.base64_encodeString(strPayload);
	string secret =encodedHeader+encodedPayload;
	//string encodeSecret=hashString(secret);
	string encodeSecret=sha256(secret);
	string jwt=encodedHeader+"."+encodedPayload+"."+encodeSecret;
	return jwt;
}

TokenAuthentificator::~TokenAuthentificator() {
	// TODO Auto-generated destructor stub
}

