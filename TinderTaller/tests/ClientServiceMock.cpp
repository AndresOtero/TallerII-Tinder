/*
 * ClientServiceMock.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: andres
 */

#include "ClientServiceMock.h"
#include "../include/JsonParser.h"
ClientServiceMock::ClientServiceMock() {
	// TODO Auto-generated constructor stub
	LOG(INFO)<< "Crear mock Cliente Service";

}

MemoryStruct ClientServiceMock::getClientService(const char * url){
	JsonParser jsonParser;
	Json::Value val;
	Json::Value user;
	string pass="pass";
	user["password"]=pass;
	string mail="andy@yahoo.com";
	user["email"]=mail;
	user["id"]="1";
	val["user"]=user;
	std::string jsonIdString=jsonParser.valueToString(val);
    char* c = (char*)malloc(strlen(jsonIdString.c_str())+1);
    strcpy(c,jsonIdString.c_str());
	MemoryStruct chunk;
	chunk.memory=c;
	chunk.size=strlen(jsonIdString.c_str())+1;
	chunk.status=CURLE_OK;
	return chunk;
}
MemoryStruct ClientServiceMock::postClientService(const char * url, const char * data){

}
MemoryStruct ClientServiceMock::putClientService(const char * url, const char * data){

}
MemoryStruct ClientServiceMock::deleteClientService(const char * url){

}

ClientServiceMock::~ClientServiceMock() {
	// TODO Auto-generated destructor stub
	LOG(INFO)<< "Destruir mock Cliente Service";

}

