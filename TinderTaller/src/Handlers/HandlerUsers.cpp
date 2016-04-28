/*
 * HandlerUsers.cpp
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */
#define TERCERA_POSITION 3
#include "HandlerUsers.h"

HandlerUsers::HandlerUsers(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator){
	/**Creo el handler de users**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=USERS;
}

msg_t HandlerUsers::getUser(struct http_message * hm) {
	/**Manejo el get de user, recibe un mensaje y una base de datos. Devuelve el msg correspondiente**/
	/**Json::Value val = jsonParse.stringToValue(hm->body.p);
	if(jsonParse.isNullValue(val))return badRequest("Bad Json");
	if(!val.isMember("user"))return badRequest("Bad Json");
	Json::Value user=val["user"];
	if(jsonParse.isNullValue(user))return badRequest("Bad Json");
	string a = jsonParse.getStringFromValue(user, "name");
	DBtuple tp(a);
	bool ok =DB->get(tp);**/
	msg_t msg;
	int id = httpReqParser.getId(hm);
	if (httpReqParser.idOk()) {
		LOG(INFO)<<"Busco "<< id <<" como identificador";
		string * result = new string();
		result->append(json_example);
		msg.change(OK, result);
		//Va a buscar el usuario en el Shared
		SharedClient * sharedClient = new SharedClient();
		stringstream userId;
		userId << id;
		msg_t * response = sharedClient->getUser(userId.str());
		msg.status = response->status;
		msg.body = response->body;
		delete response;
		delete sharedClient;
	} else {
		LOG(WARNING)<<"Not success";
		string * result = new string();
		result->append("Not success. Bad request");
		msg.change(BAD_REQUEST, result);
	}
	return msg;
}

msg_t HandlerUsers::postUser(struct http_message * hm) {
	/**Manejo el post de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Crea un usuario**/
	/*Candidata a funcion*/
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string user = jsonParse.getStringFromValue(val["user"], "name");
	DBtuple tp(user,hm->body.p);

	msg_t msg;
	bool ok = DB->put(tp);
	if (ok) {
		LOG(INFO)<<"Creo "<< user <<" como usuario";
		string token=tokenAuthentificator->createJsonToken(user);
		val["token"]=token;
		string * result = new string();
		result->append(jsonParse.valueToString(val));

		//Va a dar de alta el usuario en el Shared
		SharedClient * sharedClient = new SharedClient();
		string user = "";
		user.append(hm->body.p);
		msg_t * response = sharedClient->setUser(user);
		delete response->body;
		delete response;
		delete sharedClient;

		msg.change(CREATED, result);
	} else {
		LOG(WARNING)<<"Not success";
		string * result = new string();
		result->append("Not success. Bad request");
		msg.change(BAD_REQUEST, result);
	}
	return msg;
}

msg_t HandlerUsers::putUser(struct http_message * hm) {
	/**Manejo el put de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Modifica un usuario**/
	vector < string > uriVector = httpReqParser.parsePrefix(hm);
	string p = uriVector[TERCERA_POSITION];
	if (p == photoString) {
		return this->putUserUpdatePhoto(hm);
	} else {
		return this->putUserUpdateProfile(hm);
	}
}

msg_t HandlerUsers::putUserUpdateProfile(struct http_message * hm) {
	/**Manejo el put de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Modifica un usuario**/
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string a = jsonParse.getStringFromValue(val["user"], "name");
	DBtuple tp(a,hm->body.p);
	int id = httpReqParser.getId(hm);
	msg_t msg;
	bool ok = DB->put(tp);
	if (ok && httpReqParser.idOk()) {
		string * result = new string();
		result->append(json_example);
		msg.change(ACCEPTED, result);
		LOG(INFO)<<"Modifico "<< a <<" como usuario";
		LOG(INFO)<<"Modifico "<< id <<" como id_usuario";

		//Va a actualizar un usuario en el Shared
		SharedClient * sharedClient = new SharedClient();
		stringstream userId;
		userId << id;
		string user = "";
		user.append(hm->body.p);
		msg_t * response = sharedClient->updateUser(userId.str(), user);
		msg.status = response->status;
		msg.body = response->body;
		delete response;
		delete sharedClient;
	} else {
		LOG(WARNING)<<"Not success";
		string * result = new string();
		result->append("Not success. Bad request");
		msg.change(BAD_REQUEST, result);
	}
	return msg;
}

msg_t HandlerUsers::putUserUpdatePhoto(struct http_message * hm) {
	/**Manejo el put de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Modifica un usuario**/
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string a = jsonParse.getStringFromValue(val["user"], "name");
	DBtuple tp(a,hm->body.p);
	int id = httpReqParser.getId(hm);
	msg_t msg;
	bool ok = DB->put(tp);
	if (ok && httpReqParser.idOk()) {
		LOG(INFO)<<"Modifico la foto de "<< a <<" como usuario";
		string * result = new string();
		result->append(json_example);
		msg.change(ACCEPTED, result);

		//Va a actualizar la foto de un usuario en el Shared
		SharedClient * sharedClient = new SharedClient();
		stringstream userId;
		userId << id;
		string photo = "";
		photo.append(hm->body.p);
		msg_t * response = sharedClient->updateUserPhoto(userId.str(), photo);
		msg.status = response->status;
		msg.body = response->body;
		delete response;
		delete sharedClient;
	} else {
		LOG(WARNING)<<"Not success";
		string * result = new string();
		result->append("Not success. Bad request");
		msg.change(BAD_REQUEST, result);
	}
	return msg;
}

msg_t HandlerUsers::deleteUser(struct http_message * hm) {
	/**Manejo el delete de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Borro Usuario**/
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string a = jsonParse.getStringFromValue(val["user"], "name");
	DBtuple tp(a,hm->body.p);
	int id = httpReqParser.getId(hm);
	msg_t msg;
	bool ok = DB->delete_(tp);
	if (ok && httpReqParser.idOk()) {
		LOG(INFO)<<"Elimino "<< a <<" como usuario";
		LOG(INFO)<<"Elimino "<< id <<" como id_usuario";
		string * result = new string();
		result->append(json_example);
		msg.change(ACCEPTED, result);
		//Va a eliminar un usuario en el Shared
		SharedClient * sharedClient = new SharedClient();
		stringstream userId;
		userId << id;
		msg_t * response = sharedClient->deleteUser(userId.str());
		msg.status = response->status;
		msg.body = response->body;
		delete response;
		delete sharedClient;
	} else {
		LOG(WARNING)<<"Not success";
		string * result = new string();
		result->append("Not success. Bad request");
		msg.change(BAD_REQUEST, result);
	}
	return msg;
}
msg_t HandlerUsers::handleMsg(struct http_message *hm){
	if((httpReqParser.methodType(hm)!=POST)&&(!validateToken(hm))){
		return unathorized();
	}
	return handle(hm);
}
msg_t HandlerUsers::handle(struct http_message *hm) {
	/**Manejo los mensajes recibidos por el server con prefix de users.Recibe el mensaje y la base de datos. Devuelve la respuesta como un msg.**/
	MethodType methodT = httpReqParser.methodType(hm);
	msg_t msg;
	switch (methodT) {
	case POST:
		msg = this->postUser(hm);
		break;
	case GET:
		msg = this->getUser(hm);
		break;
	case PUT:
		msg = this->putUser(hm);
		break;
	case DELETE:
		msg = this->deleteUser(hm);
		break;
	default:
		string * response = new string();
		response->append("Method not allowed");
		msg.change(METHOD_NOT_ALLOWED, response);
		break;
	}
	return msg;
}

HandlerUsers::~HandlerUsers() {
	/**Destruyo el handler de users**/
}

