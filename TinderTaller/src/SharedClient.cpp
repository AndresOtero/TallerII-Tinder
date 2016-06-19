/*
 * SharedClient.cpp
 */

#include "SharedClient.h"

SharedClient::SharedClient(shared_ptr<ClientServiceInterface> clientService) {
	LOG(INFO)<< "Inicio Shared Cliente";
	this->clientService = clientService;
}


SharedClient::~SharedClient() {
	LOG(INFO)<< "Borro Shared Cliente";


}

msg_t  SharedClient::getUsers(){
	LOG(INFO)<< "Va a obtener los usuarios (getUsers)";

	const char * urlUsers = "http://tander.herokuapp.com/users";
	MemoryStruct memoryStruct = this->clientService->getClientService(urlUsers);

	LOG(INFO)<< "Va a cargar el resultado de obtener los usuarios (getUsers)";
	msg_t response ;
	response.body.append(memoryStruct.memory);
	free(memoryStruct.memory);
	if (memoryStruct.status != CURLE_OK){
		response.status = StatusCode::ERROR;
	} else {
		response.status = StatusCode::OK;
	}

	LOG(INFO)<< "FIN de obtener los usuarios (getUsers)";
	return response;
}

msg_t  SharedClient::setUser(string & user){
	LOG(INFO)<< "Va a dar de alta un nuevo usuario (setUser)";
	LOG(DEBUG)<< "El json de alta de usuario es: " << user;

	const char * urlUsers = "http://tander.herokuapp.com/users";
	MemoryStruct memoryStruct = this->clientService->postClientService(urlUsers, user.c_str());

	LOG(INFO)<< "Va a cargar el resultado de dar de alta un nuevo usuario (setUser)";
	msg_t  response;
	response.body.append(memoryStruct.memory);
	free(memoryStruct.memory);
	if (memoryStruct.status != CURLE_OK){
		response.status = StatusCode::ERROR;
	} else {
		response.status = StatusCode::CREATED;
	}

	LOG(INFO)<< "FIN de dar de alta un nuevo usuario (setUser)";
	return response;
}

msg_t  SharedClient::getUser(string userId){
	LOG(INFO)<< "Va a obtener un usuario en particular (getUser) - Id: " << userId;

	string url;
	url.append("http://tander.herokuapp.com/users/");
	url.append(userId.c_str());
	MemoryStruct memoryStruct = this->clientService->getClientService(url.c_str());

	LOG(INFO)<< "Va a cargar el resultado de obtener un usuario en particular (getUser)";
	msg_t  response;
	response.body.append(memoryStruct.memory);
	free(memoryStruct.memory);
	if (memoryStruct.status != CURLE_OK){
		response.status = StatusCode::ERROR;
	} else {
		response.status = StatusCode::OK;
	}
	LOG(INFO)<< "FIN de obtener un usuario en particular (getUser)";
	return response;
}

msg_t  SharedClient::updateUser(string userId, string & user){
	LOG(INFO)<< "Va a actualizar un usuario en particular (updateUser) - Id: " << userId;
	LOG(DEBUG)<< "El json para actualizar un usuarios es: " << user;

	string url;
	url.append("http://tander.herokuapp.com/users/");
	url.append(userId.c_str());
	MemoryStruct memoryStruct = this->clientService->putClientService(url.c_str(), user.c_str());

	LOG(INFO)<< "Va a cargar el resultado de actualizar un usuario en particular (updateUser)";
	msg_t  response ;
	response.body.append(memoryStruct.memory);
	free(memoryStruct.memory);
	if (memoryStruct.status != CURLE_OK){
		response.status = StatusCode::ERROR;
	} else {
		response.status = StatusCode::OK;
	}
	LOG(DEBUG)<<"Mensaje de vuelta:" <<response.body;
	LOG(INFO)<< "FIN de actualizar un usuario en particular (updateUser)";
	return response;
}

msg_t  SharedClient::updateUserPhoto(string userId, string & photo){
	LOG(INFO)<< "Va a actualizar la foto de un usuario en particular (updateUserPhoto) - Id: " << userId;
	LOG(DEBUG)<< "El json para actualizar la foto de un usuarios es: " << photo;

	string url;
	url.append("http://tander.herokuapp.com/users/");
	url.append(userId.c_str());
	url.append("/photo");

	MemoryStruct memoryStruct = this->clientService->putClientService(url.c_str(), photo.c_str());

	LOG(INFO)<< "Va a cargar el resultado de actualizar la foto un usuario en particular (updateUserPhoto)";
	msg_t  response ;
	response.body.append(memoryStruct.memory);
	free(memoryStruct.memory);
	if (memoryStruct.status != CURLE_OK){
		response.status = StatusCode::ERROR;
	} else {
		response.status = StatusCode::OK;
	}

	LOG(INFO)<< "FIN de actualizar la foto un usuario en particular (updateUserPhoto)";
	return response;
}

msg_t  SharedClient::deleteUser(string userId){
	LOG(INFO)<< "Va a eliminar un usuario en particular (deleteUser) - Id: " << userId;

	string url;
	url.append("http://tander.herokuapp.com/users/");
	url.append(userId.c_str());

	MemoryStruct memoryStruct = this->clientService->deleteClientService(url.c_str());

	LOG(INFO)<< "Va a cargar el resultado de eliminar un usuario en particular (deleteUser)";
	msg_t  response;
	response.body.append(memoryStruct.memory);
	free(memoryStruct.memory);
	if (memoryStruct.status != CURLE_OK){
		response.status = StatusCode::ERROR;
	} else {
		response.status = StatusCode::OK;
	}

	LOG(INFO)<< "FIN de eliminar un usuario en particular (deleteUser)";
	return response;
}

msg_t  SharedClient::getInterests(){
	LOG(INFO)<< "Va a buscar los intereses (getInterests)";

	const char * url = "http://tander.herokuapp.com/interests";
	MemoryStruct memoryStruct = this->clientService->getClientService(url);

	LOG(INFO)<< "Va a cargar el resultado de buscar los intereses (getInterests)";
	msg_t  response ;
	response.body.append(memoryStruct.memory);
	free(memoryStruct.memory);
	if (memoryStruct.status != CURLE_OK){
		response.status = StatusCode::ERROR;
	} else {
		response.status = StatusCode::OK;
	}

	LOG(INFO)<< "FIN de buscar los intereses (getInterests)";
	return response;
}


msg_t  SharedClient::setInterests(string & interests){
	LOG(INFO)<< "Va a dar de alta nuevo intereses (setInterests)";
    LOG(DEBUG)<< "El json para el alta nuevo intereses es: " << interests;

    const char * url = "http://tander.herokuapp.com/interests";
	MemoryStruct memoryStruct = this->clientService->postClientService(url, interests.c_str());

	LOG(INFO)<< "Va a cargar el resultado de dar de alta nuevo intereses (setInterests)";
	msg_t  response ;
	response.body.append(memoryStruct.memory);
	free(memoryStruct.memory);
	if (memoryStruct.status != CURLE_OK){
		response.status = StatusCode::ERROR;
	} else {
		response.status = StatusCode::CREATED;
	}

	LOG(INFO)<< "FIN de dar de alta nuevo intereses (setInterests)";
	return response;
}
