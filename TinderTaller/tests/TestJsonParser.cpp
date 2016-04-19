#include "../include/gtest/gtest.h"
#include "../include/JsonParser.h"
#include <iostream>
std::string jsonSimpleStringToint ="{ \"result\": 2 }";
std::string jsonSimpleStringToString ="{ \"result\": \"holis\" }";

TEST(JsonParser,parseSimpleStringToInt){
	JsonParser jsonParser;
	Json::Value val;
	val =jsonParser.stringToValue(jsonSimpleStringToint);
	EXPECT_TRUE(jsonParser.getIntFromValue(val,"result")==2);
}
TEST(JsonParser,parseSimpleStringToString){
	JsonParser jsonParser;
	Json::Value val;
	val =jsonParser.stringToValue(jsonSimpleStringToString);
	EXPECT_TRUE(jsonParser.getStringFromValue(val,"result")=="holis");
}
