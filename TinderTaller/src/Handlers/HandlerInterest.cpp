/*
 * HandlerInterest.cpp
 *
 *  Created on: 4 de may. de 2016
 *      Author: andres
 */

#include "HandlerInterest.h"

HandlerInterest::HandlerInterest(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificatorInterface> tokenAuthentificator,shared_ptr<SharedClient> sharedClient){
	/**Creo el handler de interest**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=INTERESTS;
	this->sharedClient=sharedClient;
}

msg_t HandlerInterest::handleGet(struct http_message *hm){
	/**Busco todos los interesemJsonString);
					 .clear();s del usuario**/
	msg_t msg=this->sharedClient->getInterests();
	Json::Value val=jsonParse.stringToValue(msg.body);
	Interest hombre;
	hombre.changeInterest("Me interesa conocer","Hombre");
	Interest mujer;
	mujer.changeInterest("Me interesa conocer","Mujer");
	val["interests"].append(hombre.getJsonValue());
	val["interests"].append(mujer.getJsonValue());
	val["metadata"]["count"]=val["metadata"]["count"].asInt()+2;
	msg.body=jsonParse.valueToString(val);
	return msg;
}
msg_t HandlerInterest::handlePost(struct http_message *hm){
	/**Creo un nuevo interes**/
	string body=jsonParse.parseBody(hm->body.p);
	return this->sharedClient->setInterests(body);
}


HandlerInterest::~HandlerInterest() {
}
