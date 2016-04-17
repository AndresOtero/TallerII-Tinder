/*
 * JsonParser.cpp
 *
 *  Created on: 16 de abr. de 2016
 *      Author: andres
 */

#include "JsonParser.h"

JsonParser::JsonParser() {
	// TODO Auto-generated constructor stub

}
Json::Value JsonParser::stringToValue(std::string jsonStr) {
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(jsonStr.c_str(), root); //parse process
	if (!parsingSuccessful) {
		LOG(INFO) << "No se parseo de manera satisfactoria";
	}else{
	LOG(INFO) << "Se parseo de manera satisfactoria";
	}
	return root;
}
int JsonParser::getIntFromValue(Json::Value jsonValue,std::string key) {
	return jsonValue[key].asInt();
}
std::string JsonParser::getStringFromValue(Json::Value jsonValue,std::string key) {
	return jsonValue[key].asString();
}

JsonParser::~JsonParser() {
	// TODO Auto-generated destructor stub
}

