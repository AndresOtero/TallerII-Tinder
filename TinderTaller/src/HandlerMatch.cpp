/*
 * HandlerMatch.cpp
 *
 *  Created on: 19 de abr. de 2016
 *      Author: andres
 */

#include "HandlerMatch.h"

HandlerMatch::HandlerMatch(shared_ptr<DataBase> DB) {
	/**Creo el handler de match**/
	this->DB=DB;
	this->prefix=MATCH;
}
bool HandlerMatch::isHandler(struct http_message *hm) {
	/**Creo el handler de users**/
	return (httpReqParser.prefixType(hm)==prefix);
}
msg_t HandlerMatch::handle(struct http_message *hm) {
	/**Manejo los mensajes recibidos por el server con prefix de users.Recibe el mensaje y la base de datos. Devuelve la respuesta como un msg.**/
	MethodType methodT = httpReqParser.methodType(hm);
	msg_t msg;
	switch (methodT) {
		case POST:
			LOG(INFO) << "Hago matches";
			msg.change(ACCEPTED,"Posted match");
			break;
		case GET:
			LOG(INFO) << "Busco matches";
			msg.change(OK,"Get match");
			break;
			/**case PUT:
			 break;
			 case DELETE:
			 break;**/
		default:
			msg.change(METHOD_NOT_ALLOWED,json_example);
			break;
	}
	return msg;
}

HandlerMatch::~HandlerMatch() {
}

