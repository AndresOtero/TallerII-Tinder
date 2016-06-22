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

MemoryStruct ClientServiceMock::getClientService(const char * url) {
	MemoryStruct chunk;

	if (strcmp("http://tander.herokuapp.com/interests", url) == 0) {
		/**Json::Value null(Json::nullValue);
		Json::Value intereses;
		intereses["interests"].append(null);
		JsonParser jsonParser;
		std::string interesesString=jsonParser.valueToString(intereses);
		**/
		std::string interesesString="";
		char* c = (char*) malloc(strlen(interesesString.c_str()) + 1);
		strcpy(c, interesesString.c_str());
		chunk.memory = c;
		chunk.size = strlen(interesesString.c_str()) + 1;
		chunk.status = CURLE_OK;
	} else if (strcmp("http://tander.herokuapp.com/users/1", url) == 0) {
		JsonParser jsonParser;
		Json::Value val;
		Json::Value user;
		string pass = "pass";
		user["password"] = pass;
		string mail = "andy@yahoo.com";
		user["email"] = mail;
		user["sex"] = "Hombre";
		user["id"] = "1";
		Json::Value interest;
		interest["category"]="Musica";
		interest["value"]="Red Hot Chilli Peppers";
		user["interests"].append( interest);
		val["user"] = user;
		std::string jsonIdString = jsonParser.valueToString(val);
		char* c = (char*) malloc(strlen(jsonIdString.c_str()) + 1);
		strcpy(c, jsonIdString.c_str());
		chunk.memory = c;
		chunk.size = strlen(jsonIdString.c_str()) + 1;
		chunk.status = CURLE_OK;
	} else if (strcmp("http://tander.herokuapp.com/users/2", url) == 0) {
		JsonParser jsonParser;
		Json::Value val;
		Json::Value user;
		string pass = "pass";
		user["password"] = pass;
		string mail = "andy@yahoo.com";
		user["email"] = mail;
		user["sex"] = "F";
		user["id"] = "1";
		val["user"] = user;
		std::string jsonIdString = jsonParser.valueToString(val);
		char* c = (char*) malloc(strlen(jsonIdString.c_str()) + 1);
		strcpy(c, jsonIdString.c_str());
		chunk.memory = c;
		chunk.size = strlen(jsonIdString.c_str()) + 1;
		chunk.status = CURLE_OK;
	}if(strcmp("http://tander.herokuapp.com/users", url) == 0){
		JsonParser jsonParser;
		Json::Value list;
		Json::Value val;
		Json::Value user;
		string pass = "pass";
		user["password"] = pass;
		string mail = "ely@yahoo.com";
		user["email"] = mail;
		user["sex"] = "Mujer";
		user["id"] = "1";
		Json::Value interest;
		interest["category"]="Musica";
		interest["value"]="Red Hot Chilli Peppers";
		user["interests"].append( interest);
		list["users"].append(user);
		std::string jsonIdString = jsonParser.valueToString(list);
		char* c = (char*) malloc(strlen(jsonIdString.c_str()) + 1);
		strcpy(c, jsonIdString.c_str());
		chunk.memory = c;
		chunk.size = strlen(jsonIdString.c_str()) + 1;
		chunk.status = CURLE_OK;
	}
	return chunk;
}
MemoryStruct ClientServiceMock::postClientService(const char * url,
		const char * data) {
	MemoryStruct chunk;
	if (strcmp(url, "http://tander.herokuapp.com/interests") == 0) {
		std::string usuario = data;
		char* c = (char*) malloc(strlen(usuario.c_str()) + 1);
		strcpy(c, usuario.c_str());
		chunk.memory = c;
		chunk.size = strlen(usuario.c_str()) + 1;
		chunk.status = CURLE_OK;
	} else if (strcmp(url, "http://tander.herokuapp.com/users") == 0) {
		std::string usuario = data;
		char* c = (char*) malloc(strlen(usuario.c_str()) + 1);
		strcpy(c, usuario.c_str());
		chunk.memory = c;
		chunk.size = strlen(usuario.c_str()) + 1;
		chunk.status = CURLE_OK;
	}

	return chunk;
}

MemoryStruct ClientServiceMock::postWithAuthorizationClientService(const char * url, const char * data,
		const char * authorization) {
	MemoryStruct chunk;
	std::string usuario = data;
	char* c = (char*) malloc(strlen(usuario.c_str()) + 1);
	strcpy(c, usuario.c_str());
	chunk.memory = c;
	chunk.size = strlen(usuario.c_str()) + 1;
	return chunk;
}

MemoryStruct ClientServiceMock::putClientService(const char * url,
		const char * data) {
	MemoryStruct chunk;
	if (strcmp(url, "http://tander.herokuapp.com/users/1") == 0) {
		std::string usuario = data;
		char* c = (char*) malloc(strlen(usuario.c_str()) + 1);
		strcpy(c, usuario.c_str());
		chunk.memory = c;
		chunk.size = strlen(usuario.c_str()) + 1;
		chunk.status = CURLE_OK;
	}else if (strcmp(url, "http://tander.herokuapp.com/users/1/photo") == 0) {
		std::string usuario = data;
		char* c = (char*) malloc(strlen(usuario.c_str()) + 1);
		strcpy(c, usuario.c_str());
		chunk.memory = c;
		chunk.size = strlen(usuario.c_str()) + 1;
		chunk.status = CURLE_OK;
	}
	return chunk;
}
MemoryStruct ClientServiceMock::deleteClientService(const char * url) {
	MemoryStruct chunk;
	if (strcmp(url, "http://tander.herokuapp.com/users/") == 0) {
		std::string usuario = "delete";
		char* c = (char*) malloc(strlen(usuario.c_str()) + 1);
		strcpy(c, usuario.c_str());
		chunk.memory = c;
		chunk.size = strlen(usuario.c_str()) + 1;
		chunk.status = CURLE_OK;
	}
	return chunk;

}

ClientServiceMock::~ClientServiceMock() {
	// TODO Auto-generated destructor stub
	LOG(INFO)<< "Destruir mock Cliente Service";

}

