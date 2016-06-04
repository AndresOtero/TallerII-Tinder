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
TEST(JsonParser,parseBody){
	JsonParser jsonParser;
	string test =jsonParser.parseBody("{{{}}}{");
	EXPECT_TRUE(test=="{{{}}}");
}
TEST(JsonParser,isNullValue){
	JsonParser jsonParser;
	Json::Value NullVal(Json::nullValue);
	EXPECT_TRUE(jsonParser.isNullValue(NullVal));
	Json::Value val;
	val =jsonParser.stringToValue(jsonSimpleStringToString);
	EXPECT_FALSE(jsonParser.isNullValue(val));
}
TEST(JsonParser,removePass){
	JsonParser jsonParser;
	Json::Value val;
	Json::Value user;
	user["password"]="jaja";
	val["user"]=user;
	EXPECT_TRUE(jsonParser.removePassword(val)=="jaja");
}
TEST(JsonParser,removeGcmId){
	JsonParser jsonParser;
	Json::Value val;
	Json::Value user;
	user["gcm_registration_id"]="jaja";
	val["user"]=user;
	EXPECT_TRUE(jsonParser.removeGcmId(val)=="jaja");
}
TEST(JsonParser,removeMember){
	JsonParser jsonParser;
	Json::Value val;
	val["Sillicon"]="jaja";
	EXPECT_TRUE(jsonParser.removeMember(val,"Sillicon")=="jaja");
}
TEST(JsonParser,getId){
	JsonParser jsonParser;
	Json::Value val;
	Json::Value user;
	user["id"]="jaja";
	val["user"]=user;
	std::string jsonIdString=jsonParser.valueToString(val);
	EXPECT_TRUE(jsonParser.getId(jsonIdString)=="jaja");
}
TEST(JsonParser,getMail){
	JsonParser jsonParser;
	Json::Value val;
	Json::Value user;
	user["email"]="jaja";
	val["user"]=user;
	std::string jsonMailString=jsonParser.valueToString(val);
	EXPECT_TRUE(jsonParser.getMail(jsonMailString)=="jaja");
}

TEST(JsonParser,getPassword){
	JsonParser jsonParser;
	Json::Value val;
	Json::Value user;
	user["password"]="jaja";
	val["user"]=user;
	std::string jsonIdString=jsonParser.valueToString(val);
	EXPECT_TRUE(jsonParser.getPassword(jsonIdString)=="jaja");
}
TEST(JsonParser,oldForNewUser){
	JsonParser jsonParser;
	Json::Value oldVal;
	Json::Value newVal;
	Json::Value user;
	Json::Value newUser;
	Json::Value metadata;
	Json::Value newMetadata;
	metadata["version"]="1111";
	newMetadata["version"]="2222";
	user["password"]="jaja";
	user["mail"]="pizza";
	oldVal["user"]=user;
	oldVal["metadata"]=metadata;
	newUser["mail"]="banana";
	newVal["user"]=newUser;
	newVal["metadata"]=newMetadata;
	Json::Value valUser=jsonParser.replaceNewUserInOldUser(newVal,oldVal);
	Json::Value customUser=valUser["user"];
	Json::Value customMeta=valUser["metadata"];
	EXPECT_TRUE(customUser["mail"].asString()=="banana");
	EXPECT_TRUE(customUser["password"].asString()=="jaja");
	EXPECT_TRUE(customMeta["version"].asString()=="2222");

}

