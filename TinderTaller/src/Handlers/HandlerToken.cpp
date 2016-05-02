/*
 * HandlerToken.cpp
 *
 *  Created on: 1 de may. de 2016
 *      Author: andres
 */

#include "HandlerToken.h"

HandlerToken::HandlerToken(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator){
	/**Creo el handler de Token**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=TOKEN;
}
msg_t HandlerToken::handle(struct http_message *hm) {
	/**Manejo los mensajes recibidos por el server con prefix de match.Recibe el mensaje. Devuelve la respuesta como un msg.**/
	MethodType methodT = httpReqParser.methodType(hm);
	msg_t msg;
	switch (methodT) {
		case POST:
			msg=handlePost(hm);
			break;
		default:
			msg=this->methodNotAllowed();
			break;
	}
	return msg;
}

msg_t HandlerToken::handlePost(struct http_message *hm) {
	/**	Recibo el post de un mensaje y devuelvo un accepted si se realizo correctamente**/
	msg_t msg;
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string user = jsonParse.getStringFromValue(val["user"], "name");
	//Chequear usuario
	string token=tokenAuthentificator->createJsonToken(user);
	val["token"]=token;
	string  result = jsonParse.valueToString(val);
	LOG(INFO) << "Mando un mensaje";
	msg.change(CREATED, result);
	return msg;
}

HandlerToken::~HandlerToken() {
	// TODO Auto-generated destructor stub
}

