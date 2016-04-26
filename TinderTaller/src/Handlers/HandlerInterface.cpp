/*
 * HandlerInterface.cpp
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */

#include "HandlerInterface.h"
/**
 HandlerInterface::HandlerInterface() {

 }
 **/
msg_t HandlerInterface::handleMsg(struct http_message *hm){
	if(!validateToken(hm)){
		return unathorized();
	}
	return handle(hm);
}
bool HandlerInterface::isHandler(struct http_message *hm) {
	/**Creo el handler de users**/
	return (httpReqParser.prefixType(hm)==prefix);
}
 bool HandlerInterface::validateToken(struct http_message *hm) {
	 Json::Value bodyJson = jsonParse.stringToValue(hm->body.p);
	 string token = jsonParse.getStringFromValue(bodyJson, "token");
	 return tokenAuthentificator->validateJsonToken(token);
}
 msg_t HandlerInterface::unathorized() {
	 msg_t msg;
	 string * result = new string();
	 result->append(json_example);
	 msg.change(UNAUTHORIZED, result);
	 return msg;
}
HandlerInterface::~HandlerInterface() {
}
