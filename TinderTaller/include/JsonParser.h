/*
 * JsonParser.h
 *
 *  Created on: 16 de abr. de 2016
 *      Author: andres
 */
#include "json/json.h"
#include "json/reader.h"
#include <iostream>
#include "easylogging++.h"

#ifndef SRC_JSONPARSER_H_
#define SRC_JSONPARSER_H_

class JsonParser {
public:
	JsonParser();
	Json::Value stringToValue(std::string jsonStr);
	virtual ~JsonParser();
};

#endif /* SRC_JSONPARSER_H_ */
