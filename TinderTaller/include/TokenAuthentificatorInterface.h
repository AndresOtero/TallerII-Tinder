/*
 * TokenAuthentificatorInterface.h
 *
 *  Created on: Jun 11, 2016
 *      Author: andres
 */
#include <iostream>
#include <string>
#include <functional>
#include <ctime>
#include "../include/easylogging++.h"
#include "../include/Base64Utils.h"
#include "../include/TimeUtils.h"
#include "../include/JsonParser.h"
#include "../include/sha256.h"
#include "../include/hmac.h"
#include "../include/DataBase.h"
#include "json/json.h"
#ifndef UTILS_TOKENAUTHENTIFICATORINTERFACE_H_
#define UTILS_TOKENAUTHENTIFICATORINTERFACE_H_

class TokenAuthentificatorInterface {

public:
	virtual std::string createJsonToken(std::string user,std::string time)=0;
	virtual	std::string createJsonToken(std::string user)=0;
	virtual	string getUserName(string jsonToken)=0;
	virtual	bool deleteJsonTokenUser(string jsonToken)=0;
	virtual	bool validateJsonToken(std::string token)=0;

};

#endif /* UTILS_TOKENAUTHENTIFICATORINTERFACE_H_ */
