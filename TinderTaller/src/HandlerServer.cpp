/*
 * HandlerServer.cpp
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */

#include "HandlerServer.h"


#include <queue>

msg_t HandlerServer::badRequest(){
	/**Devuelvo el msg  que no fue un buen request.**/
	LOG(INFO)<<"Not specified prefix";
	return msg(BAD_REQUEST, "Not specified prefix");
}
HandlerServer::HandlerServer(shared_ptr<DataBase> DB) {
	/**Asigna la base de datos al handler del server.**/
	this->DB= DB;
	shared_ptr<TokenAuthentificator> tokenAuth(new TokenAuthentificator(DB));
	shared_ptr<ClientServiceInterface> clientService(new ClientService());
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientService));
	shared_ptr<GcmClient> gcmClientAux(new GcmClient(clientService));
	this->tokenAuthentificator=tokenAuth;
	vecHandler.push_back(shared_ptr<HandlerInterface>(new HandlerUsers(DB,tokenAuthentificator,sharedClient)));
	vecHandler.push_back(shared_ptr<HandlerInterface>(new HandlerInterest(DB,tokenAuthentificator,sharedClient)));
	vecHandler.push_back(shared_ptr<HandlerInterface>(new HandlerMatch(DB,tokenAuthentificator,sharedClient,gcmClientAux)));
	vecHandler.push_back(shared_ptr<HandlerInterface>(new HandlerChat(DB,tokenAuthentificator,sharedClient,gcmClientAux)));
	vecHandler.push_back(shared_ptr<HandlerInterface>(new HandlerToken(DB,tokenAuthentificator,sharedClient)));

}

msg_t  HandlerServer::handler(struct http_message *hm) {
	/**Recibe el mensaje de htttp y devuelve el msg que el server debe responder.**/
	LOG(INFO) << "Entro al handler";	
	for(shared_ptr<HandlerInterface> hi : vecHandler){
		if(hi->isHandler(hm)){
			return hi->handleMsg(hm);
		}
	}
	return this->badRequest();
}


HandlerServer::~HandlerServer() {
	/**Elimina el handler del server.**/

}

