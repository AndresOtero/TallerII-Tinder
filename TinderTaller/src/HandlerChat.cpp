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

HandlerChat::HandlerChat(shared_ptr<DataBase> DB) {
	/**Creo el handler de match**/
	this->DB=DB;
	this->prefix=CHAT;
}

bool HandlerChat::isHandler(struct http_message *hm) {
	/**Creo el handler de match**/
	return (httpReqParser.prefixType(hm)==prefix);
}

msg_t HandlerChat::handle(struct http_message *hm) {
	/**Manejo los mensajes recibidos por el server con prefix de match.Recibe el mensaje. Devuelve la respuesta como un msg.**/
	MethodType methodT = httpReqParser.methodType(hm);
		msg_t msg;
		switch (methodT) {
			case POST:
				msg=handlePost(hm);
				break;
			default:
				string * response = new string();
				response->append("Method not allowed");
				msg.change(METHOD_NOT_ALLOWED, response);
				break;
		}
		return msg;
	}

msg_t HandlerChat::handlePost(struct http_message *hm) {
	/**	Recibo el post de un mensaje y devuelvo un accepted si se realizo correctamente**/
	msg_t msg;
	LOG(INFO) << "Mando un mensaje";
	string * response = new string();
	response->append("Posted maych");
	msg.change(ACCEPTED, response);
	return msg;
}

