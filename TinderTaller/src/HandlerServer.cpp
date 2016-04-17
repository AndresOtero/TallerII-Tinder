/*
 * HandlerServer.cpp
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */

#include "HandlerServer.h"

msg_t HandlerServer::badRequest(){
	msg_t msg;
	msg.status=BAD_REQUEST;
				msg.body="Not specified prefix";
			return msg;
}
HandlerServer::HandlerServer(const std::string& db_path) {
	// Por ahora solo configuro el path , crea una si no existe pero no borra la que existe.
	this->DB= new DataBase(db_path,true,false);
	this->handlerUsers= new HandlerUsers();
}
msg_t  HandlerServer::handler(struct http_message *hm) {
	LOG(INFO) << "Entro al handler";
	PrefixType prefixT=httpReqParser.prefixType(hm);
	switch(prefixT){
		case USERS:
			LOG(INFO) << "Entro a users";
			return handleUsers(hm);
		default:
			LOG(INFO) << "Entro a Bad request";
			return badRequest();
	}
}

msg_t HandlerServer::handleUsers(struct http_message *hm){
	MethodType methodT=httpReqParser.methodType(hm);
	msg_t msg;
	switch(methodT){
			case PUT:
				LOG(INFO) << "Entro al put";
				msg.status=OK;
				msg.body.append("{ \"result\": 2 }");
			default:
				msg.status=OK;
	}
	return msg;

}

HandlerServer::~HandlerServer() {
	delete  handlerUsers;
	delete DB;
}

