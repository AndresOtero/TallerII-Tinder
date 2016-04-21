/*
 * HandlerUsers.cpp
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */
#define TERCERA_POSITION 3
#include "HandlerUsers.h"

HandlerUsers::HandlerUsers(shared_ptr<DataBase> DB) {
	/**Creo el handler de users**/
	this->DB=DB;
	this->prefix=USERS;
}
bool HandlerUsers::isHandler(struct http_message *hm) {
	/**Creo el handler de users**/
	return (httpReqParser.prefixType(hm)==prefix);
}
msg_t HandlerUsers::getUser(struct http_message * hm) {
	/**Manejo el get de user, recibe un mensaje y una base de datos. Devuelve el msg correspondiente**/
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string a = jsonParse.getStringFromValue(val["user"], "name");
	DBtuple tp(a);
	bool ok =DB->get(tp);
	msg_t msg;
	int id = httpReqParser.getId(hm);
	if (httpReqParser.idOk()&&ok) {
		LOG(INFO)<<"Busco "<< id <<" como identificador";
		msg.change(CREATED,json_example);
	} else {
		LOG(WARNING)<<"Not success";
		msg.change(BAD_REQUEST,json_example);
	}
	return msg;
}

msg_t HandlerUsers::postUser(struct http_message * hm) {
	/**Manejo el post de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Crea un usuario**/
	/*Candidata a funcion*/
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string a = jsonParse.getStringFromValue(val["user"], "name");
	DBtuple tp(a,hm->body.p);

	msg_t msg;
	bool ok = DB->put(tp);
	if (ok) {
		LOG(INFO)<<"Creo "<< a <<" como usuario";
		msg.change(CREATED,json_example);
	} else {
		LOG(WARNING)<<"Not success";
		msg.change(BAD_REQUEST,json_example);
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
		LOG(INFO)<<"Modifico "<< a <<" como usuario";
		LOG(INFO)<<"Modifico "<< id <<" como id_usuario";
		msg.change(ACCEPTED,json_example);
	} else {
		LOG(WARNING)<<"Not success";
		msg.change(BAD_REQUEST,json_example);
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
		msg.change(ACCEPTED,json_example);
	} else {
		LOG(WARNING)<<"Not success";
		msg.change(BAD_REQUEST,json_example);
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
		msg.change(ACCEPTED,json_example);
	} else {
		LOG(WARNING)<<"Not success";
		msg.change(BAD_REQUEST,json_example);
	}
	return msg;
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
		msg.change(METHOD_NOT_ALLOWED,json_example);
		break;
	}
	return msg;
}

HandlerUsers::~HandlerUsers() {
	/**Destruyo el handler de users**/
}

