/*
 * HandlerServer.cpp
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */

#include "HandlerServer.h"

msg_t HandlerServer::badRequest(){
	/**Devuelvo el msg  que no fue un buen request.**/
	LOG(INFO)<<"Not specified prefix";
	return msg(BAD_REQUEST,"Not specified prefix");
}
HandlerServer::HandlerServer(shared_ptr<DataBase> DB) {
	/**Asigna la base de datos al handler del server.**/
	this->DB= DB;
	vecHandler.push_back(shared_ptr<HandlerInterface>(new HandlerUsers(DB)));
	vecHandler.push_back(shared_ptr<HandlerInterface>(new HandlerMatch(DB)));
	vecHandler.push_back(shared_ptr<HandlerInterface>(new HandlerChat(DB)));

}
msg_t  HandlerServer::handler(struct http_message *hm) {
	/**Recibe el mensaje de htttp y devuelve el msg que el server debe responder.**/
	LOG(INFO) << "Entro al handler";
	PrefixType prefixT=httpReqParser.prefixType(hm);
	for(shared_ptr<HandlerInterface> hi : vecHandler){
		if(hi->isHandler(hm)){
			return hi->handle(hm);
		}
	}
	return this->badRequest();
}


HandlerServer::~HandlerServer() {
	/**Elimina el handler del server.**/

}

