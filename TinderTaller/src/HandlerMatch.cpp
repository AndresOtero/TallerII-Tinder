/*
 * HandlerMatch.cpp
 *
 *  Created on: 19 de abr. de 2016
 *      Author: andres
 */

#include "HandlerMatch.h"
const string json_example = "{\"holis\" :\"andy\" }";

HandlerMatch::HandlerMatch() {

}
msg_t HandlerMatch::handle(struct http_message *hm, shared_ptr<DataBase> db) {
	/**Manejo los mensajes recibidos por el server con prefix de users.Recibe el mensaje y la base de datos. Devuelve la respuesta como un msg.**/
	MethodType methodT = httpReqParser.methodType(hm);
	msg_t msg;
	switch (methodT) {
	case POST:
		LOG(INFO) << "Hago matches";
		break;
	case GET:
		LOG(INFO) << "Busco matches";
		break;
		/**case PUT:
		 break;
		 case DELETE:
		 break;**/
	default:
		msg.status = METHOD_NOT_ALLOWED;
		msg.body.append(json_example);
		break;
	}
	return msg;
}

HandlerMatch::~HandlerMatch() {
}

