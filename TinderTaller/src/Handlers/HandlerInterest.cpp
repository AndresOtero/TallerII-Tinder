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

msg_t HandlerInterest::handleGet(struct http_message *hm){
	/**Busco todos los intereses del usuario**/
	return this->sharedClient->getInterests();
}
msg_t HandlerInterest::handlePost(struct http_message *hm){
	/**Creo un nuevo interes**/
	string body=jsonParse.parseBody(hm->body.p);
	return this->sharedClient->setInterests(body);
}


HandlerInterest::~HandlerInterest() {
}
