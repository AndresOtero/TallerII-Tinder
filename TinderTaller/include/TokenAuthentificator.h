/*
 * TokenAuthentificator.h
 *
 *  Created on: 24 de abr. de 2016
 *      Author: andres
 */
#include <iostream>
#include <string>
#include <functional>
#include <ctime>

#include "../include/Base64Utils.h"
#include "../include/TimeUtils.h"
#include "../include/JsonParser.h"
#include "../include/sha256.h"
#include "json/json.h"

#ifndef SRC_TOKENAUTHENTIFICATOR_H_
#define SRC_TOKENAUTHENTIFICATOR_H_

class TokenAuthentificator {
private:
	Base64Utils base64Utils;
	TimeUtils timeUtils;
	JsonParser jsonParser;
	SHA256 sha256;
public:
	TokenAuthentificator();
	std::string createJsonToken(std::string user,std::string time);
	virtual ~TokenAuthentificator();
};

#endif /* SRC_TOKENAUTHENTIFICATOR_H_ */
