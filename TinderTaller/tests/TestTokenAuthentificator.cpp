/*
 * TestTokenAuthentificator.cpp
 *
 *  Created on: 25 de abr. de 2016
 *      Author: andres
 */

#include "../include/gtest/gtest.h"
#include "../include/TokenAuthentificator.h"
#include "../include/Base64Utils.h"
#include <iostream>
using namespace std;

TEST(TokenAuthentificator,askTokenVerificateToken){
	TokenAuthentificator token;
	string strTime ="25-04-2016 11:09:16";
	string strToken=token.createJsonToken("andy",strTime);
	EXPECT_EQ(strToken,"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9Cg==.eyJ0aW1lIjoiMjUtMDQtMjAxNiAxMTowOToxNiIsInVzZXIiOiJhbmR5In0K.4cc4ffc7cf1091e3b4a510adaf5474d3843fa85b7a561f900d82021380f3b16f");


}
TEST(TokenAuthentificator,askTokenVerificateUser){
	TokenAuthentificator token;
	Base64Utils base64;
	JsonParser json;
	string strTime = "25-04-2016 11:09:16";
	string strToken = token.createJsonToken("andy", strTime);
	size_t firstDot = strToken.find_first_of(".");
	size_t lastDot = strToken.find_last_of(".");
	string strPayloadEncoded = strToken.substr(firstDot + 1,
			lastDot - firstDot - 1);
	string strPayloadDecoded = base64.base64_decode(strPayloadEncoded);
	Json::Value val = json.stringToValue(strPayloadDecoded);
	string user = json.getStringFromValue(val, "user");
	EXPECT_EQ(user, "andy");
}
TEST(TokenAuthentificator,askTokenVerificateTime){
	TokenAuthentificator token;
	Base64Utils base64;
	JsonParser json;
	string strTime = "25-04-2016 11:09:16";
	string strToken = token.createJsonToken("andy", strTime);
	size_t firstDot = strToken.find_first_of(".");
	size_t lastDot = strToken.find_last_of(".");
	string strPayloadEncoded = strToken.substr(firstDot + 1,
			lastDot - firstDot - 1);
	string strPayloadDecoded = base64.base64_decode(strPayloadEncoded);
	Json::Value val = json.stringToValue(strPayloadDecoded);
	string time = json.getStringFromValue(val, "time");
	EXPECT_EQ(time, "25-04-2016 11:09:16");
}
