#include "../include/gtest/gtest.h"
#include "../include/JsonParser.h"
#include <iostream>
std::string jsonSimpleString ="{ \"result\": 2 }";

TEST(JsonParser,parseSimpleString){
	JsonParser jsonParser;
	Json::Value val;
	val =jsonParser.stringToValue(jsonSimpleString);
	EXPECT_TRUE(jsonParser.getIntFromValue(val,"result")==2);
}
