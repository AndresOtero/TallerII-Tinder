/*
 * SharedClient.cpp
 */

#include "SharedClient.h"

SharedClient::SharedClient(shared_ptr<ClientServiceInterface> clientService) {
	/**Constructor del shared client**/
	LOG(INFO)<< "Inicio Shared Cliente";
	this->clientService = clientService;
 	this->urlSharedServer= Configuration::getConfiguration()->getStringAttribute("urlSharedServer");
}


SharedClient::~SharedClient() {
	/**Destructor del shared client**/
	LOG(INFO)<< "Borro Shared Cliente";
}

msg_t  SharedClient::getUsers(){
	/**Obtiene los usuarios del shared server**/
	LOG(INFO)<< "Va a obtener los usuarios (getUsers)";

	string urlUsers = urlSharedServer+"/users";
	MemoryStruct memoryStruct = this->clientService->getClientService(urlUsers.c_str());

	LOG(INFO)<< "Va a cargar el resultado de obtener l os usuarios (getUsers)";
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
	/**Crea un nuevo usuario en el  shared server**/
	LOG(INFO)<< "Va a dar de alta un nuevo usuario (setUser)";
	LOG(DEBUG)<< "El json de alta de usuario es: " << user;

	string urlUsers = urlSharedServer+"/users";
	MemoryStruct memoryStruct = this->clientService->postClientService(urlUsers.c_str(), user.c_str());

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
	/**Busca un usuario en el  shared server con el id recibido**/

	LOG(INFO)<< "Va a obtener un usuario en particular (getUser) - Id: " << userId;

	string url=urlSharedServer;
	url.append("/users/");
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
	/**Actualiza un usuario en el  shared server con el id recibido**/

	LOG(INFO)<< "Va a actualizar un usuario en particular (updateUser) - Id: " << userId;
	LOG(DEBUG)<< "El json para actualizar un usuarios es: " << user;

	string url=urlSharedServer;
	url.append("/users/");
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
	/**Actualiza la foto de un usuario en el  shared server con el id recibido**/
	LOG(INFO)<< "Va a actualizar la foto de un usuario en particular (updateUserPhoto) - Id: " << userId;
	LOG(DEBUG)<< "El json para actualizar la foto de un usuarios es: " << photo;

	string url=urlSharedServer;
	url.append("/users/");
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
	/**Borra un usuario en el  shared server con el id recibido**/
	LOG(INFO)<< "Va a eliminar un usuario en particular (deleteUser) - Id: " << userId;

	string url=urlSharedServer;
	url.append("/users/");
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
	/**Busca los intereses del shared server**/
	LOG(INFO)<< "Va a buscar los intereses (getInterests)";

	string url = urlSharedServer+"/interests";
	MemoryStruct memoryStruct = this->clientService->getClientService(url.c_str());

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
	/**Da de alta un nuevo interes en el shared server**/
	LOG(INFO)<< "Va a dar de alta nuevo intereses (setInterests)";
    LOG(DEBUG)<< "El json para el alta nuevo intereses es: " << interests;

    string url = urlSharedServer+"/interests";
	MemoryStruct memoryStruct = this->clientService->postClientService(url.c_str(), interests.c_str());

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
