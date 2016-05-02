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
	string token =httpReqParser.getTokenFromHeader(hm);
	return tokenAuthentificator->validateJsonToken(token);
}
 msg_t HandlerInterface::unathorized() {
	 msg_t msg;
	 msg.change(UNAUTHORIZED, json_example);
	 return msg;
}
 msg_t HandlerInterface::badRequest(string strMsg) {
	 msg_t msg;
	 msg.change(BAD_REQUEST, strMsg);
	 return msg;
}
 msg_t HandlerInterface::methodNotAllowed() {
	 msg_t msg;
	 msg.change(BAD_REQUEST, "Method not allowed");
	 return msg;
}
HandlerInterface::~HandlerInterface() {
}
