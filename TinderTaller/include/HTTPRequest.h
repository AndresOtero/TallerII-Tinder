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

typedef enum StatusCode {
	OK = 200,CREATED=201,ACCEPTED=202, BAD_REQUEST = 400, UNAUTHORIZED = 401, NOT_FOUND = 404,METHOD_NOT_ALLOWED=405,INTERNAL_ERROR = 500,
	NOT_IMPLEMENTED=501, DEFAULT_CODE = 0, ERROR = 1, ERROR_LIMIT_DAILY_STATUS_CODE = 402
} StatusCode;

typedef struct msg{
	StatusCode status;
	string  body;
	/**msg(StatusCode status,string body){
		this->body=body;
		this->status=status;
	}**/
	msg(StatusCode status,string  body){
		change(status,body);
	}
	void change(StatusCode status,string  body){
		this->body = body;
		this->status = status;
	}
	msg(){};
}msg_t;


const string putString="PUT";
const string getString="GET";
const string postString="POST";
const string deleteString="DELETE";
const string invalidMethodString="INVALID_METHOD";

typedef enum MethodType {
	POST, PUT, GET, DELETE, INVALID_METHOD
} MethodType;

const string usersString="users";
const string matchString="match";
const string chatString="chat";
const string photoString="photo";
const string tokenString="token";
const string interestsString="interests";


typedef enum PrefixType {
	USERS,MATCH,CHAT,TOKEN,INTERESTS,INVALID_PREFIX,
} PrefixType;

#endif /* INCLUDE_HTTPREQUEST_H_ */
