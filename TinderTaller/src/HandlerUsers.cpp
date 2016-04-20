/*
 * HandlerUsers.cpp
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */
#define TERCERA_POSITION 3
#include "HandlerUsers.h"
const string json_example = "{\"holis\" :\"andy\" }";
HandlerUsers::HandlerUsers() {
	/**Creo el handler de users**/
}
msg_t HandlerUsers::getUser(struct http_message * hm, DataBase* db) {
	/**Manejo el get de user, recibe un mensaje y una base de datos. Devuelve el msg correspondiente**/
	msg_t msg;
	int id = httpReqParser.getId(hm);
	if (id >= 0) {
		LOG(INFO)<<"Busco "<< id <<" como identificador";
		msg.status = OK;
		msg.body.append(json_example); //aca va el client o la base de datos
	} else {
		LOG(WARNING)<<"Not success, id not int.";
		msg.status = BAD_REQUEST;
		msg.body.append(json_example);
	}
	return msg;
}
msg_t HandlerUsers::postUser(struct http_message * hm, DataBase* db) {
	/**Manejo el post de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Crea un usuario**/
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string a = jsonParse.getStringFromValue(val["user"], "name");
	DBtuple tp;
	tp.key = a;
	tp.value = hm->body.p;
	msg_t msg;
	bool ok = db->put(tp);
	if (ok) {
		LOG(INFO)<<"Creo "<< a <<" como usuario";
		msg.status = CREATED;
		msg.body.append(json_example);
	} else {
		LOG(WARNING)<<"Not success";
		msg.status = BAD_REQUEST;
		msg.body.append(json_example);
	}
	return msg;
}
msg_t HandlerUsers::putUser(struct http_message * hm, DataBase* db) {
	/**Manejo el put de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Modifica un usuario**/
	vector<string> uriVector=httpReqParser.parsePrefix(hm);
	string p=uriVector[TERCERA_POSITION];
	if(p==photoString){
		return this->putUserUpdatePhoto(hm,db);
	}else{
		return this->putUserUpdateProfile(hm,db);
	}
}

msg_t HandlerUsers::putUserUpdateProfile(struct http_message * hm, DataBase* db) {
	/**Manejo el put de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Modifica un usuario**/
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string a = jsonParse.getStringFromValue(val["user"], "name");
	DBtuple tp;
	tp.key = a;
	tp.value = hm->body.p;
	int id = httpReqParser.getId(hm);
	msg_t msg;
	bool ok = db->put(tp);
	if (ok&&httpReqParser.idOk(id)) {
		LOG(INFO)<<"Modifico "<< a <<" como usuario";
		LOG(INFO)<<"Modifico "<< id <<" como id_usuario";
		msg.status = ACCEPTED;
		msg.body.append(json_example);
	} else {
		LOG(WARNING)<<"Not success";
		msg.status = BAD_REQUEST;
		msg.body.append(json_example);
	}
	return msg;
}

msg_t HandlerUsers::putUserUpdatePhoto(struct http_message * hm, DataBase* db) {
	/**Manejo el put de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Modifica un usuario**/
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string a = jsonParse.getStringFromValue(val["user"], "name");
	DBtuple tp;
	tp.key = a;
	tp.value = hm->body.p;
	int id = httpReqParser.getId(hm);
	msg_t msg;
	bool ok = db->put(tp);
	if (ok&&httpReqParser.idOk(id)) {
		LOG(INFO)<<"Modifico la foto de "<< a <<" como usuario";
		msg.status = ACCEPTED;
		msg.body.append(json_example);
	} else {
		LOG(WARNING)<<"Not success";
		msg.status = BAD_REQUEST;
		msg.body.append(json_example);
	}
	return msg;
}


msg_t HandlerUsers::deleteUser(struct http_message * hm, DataBase* db) {
	/**Manejo el delete de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Borro Usuario**/
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string a = jsonParse.getStringFromValue(val["user"], "name");
	DBtuple tp;
	tp.key = a;
	tp.value = hm->body.p;
	int id = httpReqParser.getId(hm);
	msg_t msg;
	bool ok = db->put(tp);
	if (ok&&httpReqParser.idOk(id)) {
		LOG(INFO)<<"Elimino "<< a <<" como usuario";
		LOG(INFO)<<"Elimino "<< id <<" como id_usuario";
		msg.status = ACCEPTED;
		msg.body.append(json_example);
	} else {
		LOG(WARNING)<<"Not success";
		msg.status = BAD_REQUEST;
		msg.body.append(json_example);
	}
	return msg;
}

msg_t HandlerUsers::handle(struct http_message *hm, DataBase* db) {
	/**Manejo los mensajes recibidos por el server con prefix de users.Recibe el mensaje y la base de datos. Devuelve la respuesta como un msg.**/
	MethodType methodT = httpReqParser.methodType(hm);
	msg_t msg;
	switch (methodT) {
	case POST:
		msg = this->postUser(hm, db);
		break;
	case GET:
		msg = this->getUser(hm, db);
		break;
	case PUT:
		msg =this->putUser(hm,db);
		break;
	case DELETE:
		msg =this->deleteUser(hm,db);
		break;
	default:
		msg.status = METHOD_NOT_ALLOWED;
		msg.body.append(json_example);
		break;
	}
	return msg;
}

HandlerUsers::~HandlerUsers() {
	/**Destruyo el handler de users**/
}

