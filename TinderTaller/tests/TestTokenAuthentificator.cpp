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
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	TokenAuthentificator token(db);
	string strTime ="25-04-2016 11:09:16";
	string strToken=token.createJsonToken("andy",strTime);
	EXPECT_EQ(strToken,"ewogICAiYWxnIiA6ICJIUzI1NiIsCiAgICJ0eXAiIDogIkpXVCIKfQo=.ewogICAidGltZSIgOiAiMjUtMDQtMjAxNiAxMTowOToxNiIsCiAgICJ1c2VyIiA6ICJhbmR5Igp9Cg==.MGM5OTJkMWZhNDM1NTFjMzRlZDQzMTBlMDg4MzgwYWEwNTgzNzBkZWUzOTM3MTdhZGEzMDQwYmJhYmM5ZjE3Zg==");
}
TEST(TokenAuthentificator,askTokenVerificateUser){
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	TokenAuthentificator token(db);
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
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	TokenAuthentificator token(db);
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
TEST(TokenAuthentificator,notValidateNotFormattedToken){
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	TokenAuthentificator token(db);
	EXPECT_FALSE(token.validateJsonToken("holis"));
}
TEST(TokenAuthentificator,notValidateWrongSignature){
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	TokenAuthentificator token(db);
	TimeUtils timeUtils;
	string strTime = timeUtils.timeToString();
	string strToken = token.createJsonToken("andy", strTime);
	strToken += "x";
	EXPECT_FALSE(token.validateJsonToken(strToken));
}
TEST(TokenAuthentificator,notValidateExperatedToken){
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	TokenAuthentificator token(db);
	string strTime = "25-04-2010 11:09:16";
	string strToken = token.createJsonToken("andy", strTime);
	EXPECT_FALSE(token.validateJsonToken(strToken));
}
TEST(TokenAuthentificator,validateTokenWithTimeStamp){
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	TokenAuthentificator token(db);
	TimeUtils timeUtils;
	string strTime = timeUtils.timeToString();
	string strToken = token.createJsonToken("andy", strTime);
	EXPECT_TRUE(token.validateJsonToken(strToken));
}
TEST(TokenAuthentificator,validateTokenWithOutTimeStamp){
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	TokenAuthentificator token(db);
	EXPECT_TRUE(token.validateJsonToken(token.createJsonToken("andy")));
}
TEST(TokenAuthentificator,deleteJsonTokenUser){
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	TokenAuthentificator token(db);
	string tokenString=token.createJsonToken("andy");
	EXPECT_TRUE(token.deleteJsonTokenUser(tokenString));
}
