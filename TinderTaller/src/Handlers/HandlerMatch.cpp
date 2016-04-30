/*
 * HandlerMatch.cpp
 *
 *  Created on: 19 de abr. de 2016
 *      Author: andres
 */

#include "HandlerMatch.h"

HandlerMatch::HandlerMatch(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator) {
	/**Creo el handler de match**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=MATCH;
}

msg_t HandlerMatch::handle(struct http_message *hm) {
	/**Manejo los mensajes recibidos por el server con prefix de users.Recibe el mensaje y la base de datos. Devuelve la respuesta como un msg.**/
	MethodType methodT = httpReqParser.methodType(hm);
	msg_t msg;
	switch (methodT) {
		case POST:
			msg=handlePost(hm);
			break;
		case GET:
			msg=handleGet(hm);
			break;
		default:
			msg=this->methodNotAllowed();
			break;
	}
	return msg;
}

msg_t HandlerMatch::handlePost(struct http_message *hm){
	/**Recibo el post de un match y devuelvo un Accepted en caso de exito.**/
	msg_t msg;
	msg.change(ACCEPTED, "Posted maych");
	return msg;
}

msg_t HandlerMatch::handleGet(struct http_message *hm){
	/**Recibo el get de un match y devuelvo un Ok en caso de exito.**/
	msg_t msg;
	LOG(INFO) << "Busco matches";
	msg.change(OK, "Get match");
	return msg;
}

HandlerMatch::~HandlerMatch() {
	/**Destruyo el handler de Match**/

}

