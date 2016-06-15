/*
 * Configuration.h
 *
 *  Created on: Jun 14, 2016
 *      Author: andres
 */
#include <iostream>
#include <string.h>
#include "JsonParser.h"
#include "easylogging++.h"

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_
using namespace std;
class Configuration {
private:
	static string pathJson;
	Json::Value jsonFile;
	JsonParser jsonParser;
	static bool set;
	static shared_ptr<Configuration> configurationInstance;
	Configuration(const char* path);
public:
	static void setPath(string path);
	static shared_ptr<Configuration> getConfiguration();
	string getStringAttribute(string attribute );
	bool getBooleanAttribute(string attribute );
	virtual ~Configuration();
};

#endif /* CONFIGURATION_H_ */
