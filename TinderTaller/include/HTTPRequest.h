/*
 * HTTPRequest.h
 *
 *  Created on: 16 de abr. de 2016
 *      Author: andres
 */
#include <iostream>

#ifndef INCLUDE_HTTPREQUEST_H_
#define INCLUDE_HTTPREQUEST_H_
using namespace std;

typedef struct msg{
	int status;
	string body;
}msg_t;

typedef enum StatusCode {
	OK = 200,CREATED=201, BAD_REQUEST = 400, UNAUTHORIZED = 401, NOT_FOUND = 404,
	//CONFLICT = 409,
	INTERNAL_ERROR = 500
} StatusCode;

const string putString="PUT";
const string getString="GET";
const string postString="POST";
const string deleteString="DELETE";
const string invalidMethodString="INVALID_METHOD";

typedef enum MethodType {
	POST, PUT, GET, DELETE, INVALID_METHOD
} MethodType;

const string usersString="/users";


typedef enum PrefixType {
	USERS
} PrefixType;




#endif /* INCLUDE_HTTPREQUEST_H_ */
