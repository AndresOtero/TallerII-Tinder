/*
 * HandlerServer.cpp
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */

#include "HandlerServer.h"

msg_t HandlerServer::badRequest(){
	/**Devuelvo el msg  que no fue un buen request.**/
	msg_t msg;
	msg.status=BAD_REQUEST;
				msg.body="Not specified prefix";
			return msg;
}
HandlerServer::HandlerServer(DataBase *DB) {
	/**Asigna la base de datos al handler del server.**/
	this->DB= DB;
}
msg_t  HandlerServer::handler(struct http_message *hm) {
	/**Recibe el mensaje de htttp y devuelve el msg que el server debe responder.**/
	LOG(INFO) << "Entro al handler";
	PrefixType prefixT=httpReqParser.prefixType(hm);
	switch(prefixT){
		case USERS:
			LOG(INFO) << "Entro a users";
			return this->handlerUsers.handle(hm,DB);
		case MATCHS:

		default:
			LOG(WARNING) << "Entro a Bad request";
			return badRequest();
	}
}


HandlerServer::~HandlerServer() {
	/**Elimina el handler del server.**/

	delete DB;
}

