/*
 * HandlerUsers.cpp
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */

#include "HandlerUsers.h"
string json_example = "{\"holis\" :\"andy\" }";
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
	/**Manejo el post de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente**/
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
msg_t HandlerUsers::handle(struct http_message *hm, DataBase* db) {
	/**Manejo los mensajes recibidos por el server con prefix de users.Recibe el mensaje y la base de datos. Devuelve la respuesta como un msg.**/
	MethodType methodT = httpReqParser.methodType(hm);
	msg_t msg;
	bool ok;
	switch (methodT) {
	case POST:
		msg = this->postUser(hm, db);
		break;
	case GET:
		msg = this->getUser(hm, db);
		break;
	default:
		msg.status = OK;
		msg.body.append(json_example);
		break;
	}
	return msg;
}

HandlerUsers::~HandlerUsers() {
	/**Destruyo el handler de users**/
}

