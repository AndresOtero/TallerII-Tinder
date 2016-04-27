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

Json::Value JsonParser::stringToValue(std::string jsonStr) {
	/**Recibo un string y lo devuelvo con Value de Json.**/
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
	Json::FastWriter fastWriter;
	return fastWriter.write(value);
}
int JsonParser::getIntFromValue(Json::Value jsonValue, std::string key) {
	/**Devuelvo el valor entero que esta registrado en el value de Json con la key**/
	return jsonValue[key].asInt();
}

std::string JsonParser::getStringFromValue(Json::Value jsonValue,
		std::string key) {
	/**Devuelvo un string que esta registrado en el value de Json con la key**/
	return jsonValue[key].asString();
}

JsonParser::~JsonParser() {
	/**Destruyo el parser de Json**/
}
