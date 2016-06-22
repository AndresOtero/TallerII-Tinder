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
	/**Valida el token y luego manda el mensaje al handler**/
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
	/**Metodo que maneja el handle del post por definicion no esta permitido **/
	return this->methodNotAllowed();
}

msg_t HandlerInterface::handleGet(struct http_message *hm){
	/**Metodo que maneja el handle del get por definicion no esta permitido **/
	return this->methodNotAllowed();
}

msg_t HandlerInterface::handlePut(struct http_message *hm){
	/**Metodo que maneja el handle del put por definicion no esta permitido **/
	return this->methodNotAllowed();
}

msg_t HandlerInterface::handleDelete(struct http_message *hm){
	/**Metodo que maneja el handle delete por definicion no esta permitido **/
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
	 /**Valida el token del mensaje**/
	string token =httpReqParser.getTokenFromHeader(hm);
	return tokenAuthentificator->validateJsonToken(token);
}
 bool HandlerInterface::deleteToken(struct http_message *hm) {
	 /**Borra el token del mensaje**/
	string token =httpReqParser.getTokenFromHeader(hm);
	return tokenAuthentificator->deleteJsonTokenUser(token);
}
 Json::Value HandlerInterface::loadUserPreferences(Json::Value val,string userId){
 	Json::Value preferences;
 	DBtuple userPreferenceTp(userId+"_preferences");
 	DB->get(userPreferenceTp);
 	preferences=jsonParse.stringToValue(userPreferenceTp.value);
 	Json::Value newInterests;
 	Json::Value user=val["user"];
 	if(user.isMember("interests")){
 		Json::Value interests=user["interests"];
 		for( Json::ValueIterator itr = preferences["preferences"].begin() ; itr != preferences["preferences"].end() ; itr++ ){
 			LOG(INFO)<<"Interes"<<jsonParse.valueToString(*itr);
 			interests.append(*itr);
 		}
 		user["interests"]=interests;
 	}
 	val["user"]=user;
 	return val;
 }
 string HandlerInterface::getUser(struct http_message *hm){
	 /**Devuelve el usuario que manda el mensaje**/
		string token = httpReqParser.getTokenFromHeader(hm);
		string user=tokenAuthentificator->getUserName(token);
		return user;
 }

 msg_t HandlerInterface::unathorized() {
	 /**Devuelve un mensaje con status no autorizado**/
	 msg_t msg;
	 msg.change(UNAUTHORIZED, json_example);
	 return msg;
}
 msg_t HandlerInterface::badRequest(string strMsg) {
	 /**Devuelve un mensaje con status bad request**/
	 msg_t msg;
	 msg.change(BAD_REQUEST, strMsg);
	 return msg;
}
 msg_t HandlerInterface::methodNotAllowed() {
	 /**Devuelve un mensaje con status de metodo no permitido**/
	 msg_t msg;
	 msg.change(BAD_REQUEST, "Method not allowed");
	 return msg;
}
HandlerInterface::~HandlerInterface() {
}
