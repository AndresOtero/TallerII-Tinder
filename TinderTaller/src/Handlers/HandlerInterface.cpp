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

msg_t HandlerInterface::handlePost(struct http_message *hm){
	return this->methodNotAllowed();
}

msg_t HandlerInterface::handleGet(struct http_message *hm){
	return this->methodNotAllowed();
}

msg_t HandlerInterface::handlePut(struct http_message *hm){
	return this->methodNotAllowed();
}

msg_t HandlerInterface::handleDelete(struct http_message *hm){
	return this->methodNotAllowed();
}

msg_t HandlerInterface::handle(struct http_message *hm) {
	/**Manejo los mensajes recibidos por el server con prefix de users.Recibe el mensaje y la base de datos. Devuelve la respuesta como un msg.**/
	MethodType methodT = httpReqParser.methodType(hm);
	msg_t msg;
	switch (methodT) {
	case POST:
		msg = this->handlePost(hm);
		break;
	case GET:
		msg = this->handleGet(hm);
		break;
	case PUT:
		msg = this->handlePut(hm);
		break;
	case DELETE:
		msg = this->handleDelete(hm);
		break;
	default:
		msg=this->methodNotAllowed();
		break;
	}
	return msg;
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
