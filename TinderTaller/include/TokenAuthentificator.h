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
#include "../include/easylogging++.h"
#include "../include/Base64Utils.h"
#include "../include/TimeUtils.h"
#include "../include/JsonParser.h"
#include "../include/sha256.h"
#include "../include/hmac.h"
#include "../include/DataBase.h"
#include "json/json.h"

#ifndef SRC_TOKENAUTHENTIFICATOR_H_
#define SRC_TOKENAUTHENTIFICATOR_H_

class TokenAuthentificator {
private:
	Base64Utils base64Utils;
	TimeUtils timeUtils;
	JsonParser jsonParser;
	shared_ptr<DataBase> DB;
	const string key="secret";
	const string alg="HS256";
	const string type="JWT";
	const double experationTime=31536000;//Un año
	//const double experationTime=60;
	string createJsonTokenHeader();
	string createJsonTokenPayload(string user, string time) ;
	string createJsonTokenSignature(string encodedHeader, string encodedPayload);
	string getPayloadDecoded(string jsonToken);
	string getSingature(string jsonToken);
	string getTokenTime(string jsonToken);
	bool validateJsonTokenTime(string jsonToken);
	bool validateJsonTokenUser(string jsonToken);
	bool validateJsonTokenSignature(string jsonToken);
public:
	TokenAuthentificator(shared_ptr<DataBase> DB);
	std::string createJsonToken(std::string user,std::string time);
	std::string createJsonToken(std::string user);
	string getUserName(string jsonToken);
	bool deleteJsonTokenUser(string jsonToken);

	bool validateJsonToken(std::string token);


	virtual ~TokenAuthentificator();

};

#endif /* SRC_TOKENAUTHENTIFICATOR_H_ */
