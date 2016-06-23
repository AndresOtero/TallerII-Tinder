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
	/**Constructor del gcm Client**/
	LOG(INFO)<< "Inicio Gcm Cliente";
	this->clientService = clientService;
}

GcmClient::~GcmClient() {
	/**Destructor del gcm Client**/

	LOG(INFO)<< "Borro Gcm Cliente";
}

msg_t GcmClient::setInGcm(string & data){
	/**Hago un POST con la data recibida**/
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
msg_t GcmClient::setNewRead(string & readMatch){
	LOG(INFO)<< "Va a informar un nuevo read (GcmClient - setNewRead)";
	LOG(DEBUG)<< "El json para el nuevo read es: " << readMatch;
	msg_t  response = setInGcm(readMatch);
	LOG(INFO)<< "FIN de dar de alta un nuevo read (GcmClient - setNewRead)";
	return response;
}

msg_t GcmClient::setNewMatch(string & dataMatch){
	/**Mando un mensaje de que hay un nuevo match al usuario correspondiente**/
	LOG(INFO)<< "Va a informar un nuevo match (GcmClient - setNewMatch)";
	LOG(DEBUG)<< "El json para el nuevo match es: " << dataMatch;

	msg_t  response = setInGcm(dataMatch);

	LOG(INFO)<< "FIN de dar de alta un nuevo match (GcmClient - setNewMatch)";
	return response;
}

msg_t GcmClient::setNewChat(string & dataChat){
	/**Mando un mensaje de que hay un nuevo mensaje al usuario correspondiente**/
	LOG(INFO)<< "Va a informar un nuevo chat (GcmClient - setNewChat)";
	LOG(DEBUG)<< "El json para el nuevo chat es: " << dataChat;

	msg_t  response = setInGcm(dataChat);

	LOG(INFO)<< "FIN de dar de alta un nuevo chat (GcmClient - setNewChat)";
	return response;
}
