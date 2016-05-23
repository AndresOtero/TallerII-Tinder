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

	LOG(INFO) << "Obteniendo los datos para guardar el mensaje del chat.";
	HTTPRequestParser hTTPRequestParser;
	string keyToken = hTTPRequestParser.getTokenFromHeader(hm);

	int pos = keyToken.find("=");
	string key = keyToken.substr(pos+1);

	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string value = jsonParse.removeMember(val, "notification");

	DBtuple chat(key, value);

	LOG(INFO) << "Voy a guardar mensaje del chat.";
	bool okPutChat = DB->put(chat);
	if (!okPutChat){
		msg.change(INTERNAL_ERROR, "{\"Mensaje\":\"Error guardando mensaje del chat.\"}");
	} else {
		msg.change(ACCEPTED, "Posted maych");
	}

	return msg;
}

msg_t HandlerChat::handleMsg(struct http_message *hm){
	/*if(!validateToken(hm)){
		return unathorized();
	}*/

	//TODO VER QUE VAMOS A HACER ACA XQ EL TOKEN VIENE DE GOOGLE. PREG SI ES ASI
	return handle(hm);
}
