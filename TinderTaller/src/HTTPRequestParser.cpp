/*
 * HTTPRequestParser.cpp
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */

#include "HTTPRequestParser.h"
using namespace std;
HTTPRequestParser::HTTPRequestParser() {

}
bool HTTPRequestParser::isPrefix(struct http_message *hm, string prefix){
	return (mg_vcmp(&hm->uri, prefix.c_str()) == 0);
}
bool HTTPRequestParser::isMethod(struct http_message *hm, string method){
	string methodM="";
	methodM.append(hm->method.p, hm->method.len);
	return (methodM.compare(method)==0);
}
PrefixType HTTPRequestParser::prefixType(struct http_message *hm){
	if(isPrefix(hm,usersString)) return USERS;
}

MethodType HTTPRequestParser::methodType(struct http_message *hm){
	if(isMethod(hm,putString)) return PUT;
	if(isMethod(hm,postString)) return POST;
	if(isMethod(hm,getString)) return GET;
	if(isMethod(hm,deleteString)) return DELETE;
	if(isMethod(hm,invalidMethodString)) return INVALID_METHOD;**/
}
HTTPRequestParser::~HTTPRequestParser() {
}

