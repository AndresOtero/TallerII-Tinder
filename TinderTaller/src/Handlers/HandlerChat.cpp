/*
 * HandlerChat.cpp
 *
 *  Created on: 21 de abr. de 2016
 *      Author: andres
 */

#include "HandlerChat.h"

HandlerChat::~HandlerChat() {
	// TODO Auto-generated destructor stub
}

HandlerChat::HandlerChat(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator) {
	/**Creo el handler de match**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=CHAT;
}



msg_t HandlerChat::handlePost(struct http_message *hm) {
	/**	Recibo el post de un mensaje y devuelvo un accepted si se realizo correctamente**/
	msg_t msg;
	LOG(INFO) << "Mando un mensaje";
	msg.change(ACCEPTED, "Posted maych");
	return msg;
}

