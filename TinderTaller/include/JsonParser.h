/*
 * JsonParser.h
 *
 *  Created on: 16 de abr. de 2016
 *      Author: andres
 */
#include "json/json.h"
#include <iostream>
#include "easylogging++.h"

#ifndef SRC_JSONPARSER_H_
#define SRC_JSONPARSER_H_

class JsonParser {
	public:
		JsonParser();
		bool isNullValue(Json::Value val);
		std::string  valueToString(Json::Value value);
		Json::Value stringToValue(std::string jsonStr);
		std::string getId(std::string jsonStr);
		int getIntFromValue(Json::Value jsonValue,std::string key);
		std::string getMail(std::string jsonStr);
		std::string getStringFromValue(Json::Value jsonValue,std::string key);
		virtual ~JsonParser();
};

#endif /* SRC_JSONPARSER_H_ */
