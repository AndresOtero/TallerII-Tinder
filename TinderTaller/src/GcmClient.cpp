/*
 * GcmClient.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: ediaz
 */

#include "GcmClient.h"

const char * url = "https://fcm.googleapis.com/fcm/send";
const char * passApiGcm = "key=AIzaSyAYrHnfzOKfO4y1FxSUK5V-7tuQM4BqnE4";

GcmClient::GcmClient(shared_ptr<ClientServiceInterface> clientService) {
	LOG(INFO)<< "Inicio Gcm Cliente";
	this->clientService = clientService;
}

GcmClient::~GcmClient() {
	LOG(INFO)<< "Borro Gcm Cliente";
	//delete this->clientService;
}

msg_t GcmClient::setInGcm(string & data){
	MemoryStruct memoryStruct = this->clientService->postWithAuthorizationClientService(url, data.c_str(), passApiGcm);

	LOG(INFO)<< "Va a cargar el resultado del post en Gcm";
	msg_t response;
	response.body.append(memoryStruct.memory);
	free(memoryStruct.memory);
	if (memoryStruct.status != CURLE_OK){
		response.status = StatusCode::ERROR;
	} else {
		response.status = StatusCode::CREATED;
	}

	return response;
}

msg_t GcmClient::setNewMatch(string & dataMatch){
	LOG(INFO)<< "Va a informar un nuevo match (setNewMatch)";
	LOG(DEBUG)<< "El json para el nuevo match es: " << dataMatch;

	msg_t  response = setInGcm(dataMatch);

	LOG(INFO)<< "FIN de dar de alta un nuevo match (setNewMatch)";
	return response;
}

msg_t GcmClient::setNewChat(string & dataChat){
	LOG(INFO)<< "Va a informar un nuevo chat (setNewChat)";
	LOG(DEBUG)<< "El json para el nuevo chat es: " << dataChat;

	msg_t  response = setInGcm(dataChat);

	LOG(INFO)<< "FIN de dar de alta un nuevo chat (setNewChat)";
	return response;
}
