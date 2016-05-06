/*
 * HandlerInterest.cpp
 *
 *  Created on: 4 de may. de 2016
 *      Author: andres
 */

#include "HandlerInterest.h"

HandlerInterest::HandlerInterest(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator,shared_ptr<SharedClient> sharedClient){
	/**Creo el handler de interest**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=INTERESTS;
	this->sharedClient=sharedClient;
}

msg_t HandlerInterest::getInterest(struct http_message *hm){
	return this->sharedClient->getInterests();
}
msg_t HandlerInterest::postInterest(struct http_message *hm){
	string body(hm->body.p);
	return this->sharedClient->setInterests(body);
}

msg_t HandlerInterest::handle(struct http_message *hm) {
	/**Manejo los mensajes recibidos por el server con prefix de match.Recibe el mensaje. Devuelve la respuesta como un msg.**/
	MethodType methodT = httpReqParser.methodType(hm);
	msg_t msg;
	switch (methodT) {
			case GET:
				msg=this->getInterest(hm);
				break;
			case POST:
				msg=this->postInterest(hm);
				break;
			default:
				msg=this->methodNotAllowed();
				break;
	}
	return msg;
}

HandlerInterest::~HandlerInterest() {
}
