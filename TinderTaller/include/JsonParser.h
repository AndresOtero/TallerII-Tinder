/*
 * JsonParser.h
 *
 *  Created on: 16 de abr. de 2016
 *      Author: andres
 */
#include "json/json.h"
#include <iostream>
#include "easylogging++.h"
#include <queue>
#ifndef SRC_JSONPARSER_H_
#define SRC_JSONPARSER_H_

class JsonParser {
	public:
		JsonParser();
		Json::Value replaceNewUserInOldUser(Json::Value newVal, Json::Value  oldVal);
		std::string parseBody(std::string body);
		bool isNullValue(Json::Value val);
		std::string removePassword(Json::Value value );
		std::string removeGcmId(Json::Value val );
		std::string  valueToString(Json::Value value);
		Json::Value stringToValue(std::string jsonStr);
		std::string getId(std::string jsonStr);
		int getIntFromValue(Json::Value jsonValue,std::string key);
		std::string getMail(std::string jsonStr);
		std::string getPassword(std::string jsonStr);
		std::string getStringFromValue(Json::Value jsonValue,std::string key);
		virtual ~JsonParser();
		std::string removeMember(Json::Value val, std::string valRemove);
};

#endif /* SRC_JSONPARSER_H_ */
