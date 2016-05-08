/*
 * HandlerUsers.cpp
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */
#define TERCERA_POSITION 3
#include "HandlerUsers.h"

HandlerUsers::HandlerUsers(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator,shared_ptr<SharedClient> sharedClient){
	/**Creo el handler de users**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=USERS;
	this->sharedClient=sharedClient;
}

msg_t HandlerUsers::handleGet(struct http_message * hm) {
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
	string id = httpReqParser.getId(hm);

	if (httpReqParser.idOk()) {
		LOG(INFO)<<"Busco "<< id <<" como identificador";
		DBtuple userId(id+"_id");
		bool ok=DB->get(userId);
		if(ok){
			msg = sharedClient->getUser(userId.value);
		}
		else{
			LOG(WARNING)<<"Not success";
			msg=this->badRequest("Id isnt correct");
		}
	} else {
		LOG(WARNING)<<"Not success";
		msg=this->badRequest("Id isnt correct");
	}
	return msg;
}

bool HandlerUsers::userExists(struct http_message * hm){
	string mail = jsonParse.getMail(hm->body.p);
	DBtuple key(mail+"_id");
	return DB->get(key);
}

msg_t HandlerUsers::handlePost(struct http_message * hm) {
	/**Manejo el post de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Crea un usuario**/
	/*Candidata a funcion*/
	msg_t msg;
	string user (hm->body.p);
	bool ok;
	if(userExists(hm)){
		msg.change(BAD_REQUEST, "{\"Mensaje\":\"Usuario ya creado\"}");
		return msg;
	}
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string mail = jsonParse.getMail(hm->body.p);
	LOG(INFO)<<"Creo "<< mail <<" como usuario";
	string token=tokenAuthentificator->createJsonToken(mail);
	val["token"]=token;
	string  result = jsonParse.valueToString(val);
	//Va a dar de alta el usuario en el Shared
	LOG(INFO)<<"Mensaje: "<<user<<"\n";
	msg_t  response = sharedClient->setUser(user);
	LOG(INFO)<<"Respuesta: "<<(response.body)<<","<<response.status<<"\n";
	if (response.status==CREATED){
		string id = jsonParse.getId(response.body);
		DBtuple userId(mail+"_id",id);
		ok = DB->put(userId);
		if (!ok){
			msg.change(INTERNAL_ERROR, "{\"Mensaje\":\"Error en la creacion\"}");
			return msg;
		}
		msg.change(response.status, result);
	}
	return response;
}

msg_t HandlerUsers::handlePut(struct http_message * hm) {
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
	msg_t msg;
	string id = httpReqParser.getId(hm);
	if (httpReqParser.idOk()) {
		LOG(INFO)<<"Busco "<< id <<" como identificador";
		DBtuple userId(id+"_id");
		bool ok=DB->get(userId);
		if(ok){
			LOG(INFO)<<"Modifico "<< id <<" como usuario";
			LOG(INFO)<<"Modifico "<< userId.value <<" como id_usuario";
			//Va a actualizar un usuario en el Shared
			string user = "";
			user.append(hm->body.p);
			msg_t  response = sharedClient->updateUser(userId.value, user);
			msg.status = response.status;
			msg.body = response.body;
		}else {
			LOG(WARNING)<<"Not success";
			msg=this->badRequest("Not success");
		}
	} else {
		LOG(WARNING)<<"Not success";
		msg=this->badRequest("Not success");
	}
	return msg;
}

msg_t HandlerUsers::putUserUpdatePhoto(struct http_message * hm) {
	/**Manejo el put de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Modifica un usuario**/
	msg_t msg;
	string id = httpReqParser.getId(hm);
	if (httpReqParser.idOk()) {
		LOG(INFO)<<"Busco "<< id <<" como identificador";
		DBtuple userId(id+"_id");
		bool ok=DB->get(userId);
		if(ok){
			LOG(INFO)<<"Modifico "<< id <<" como usuario";
			LOG(INFO)<<"Modifico "<< userId.value <<" como id_usuario";
			//Va a actualizar un usuario en el Shared
			string user = "";
			user.append(hm->body.p);
			string photo = "";
			photo.append(hm->body.p);
			msg = sharedClient->updateUserPhoto(userId.value, photo);
		} else {
			LOG(WARNING)<<"Not success";
			msg=this->badRequest("Not success");
		}
	} else {
		LOG(WARNING)<<"Not success";
		msg=this->badRequest("Not success");
	}
	return msg;
}

msg_t HandlerUsers::handleDelete(struct http_message * hm) {
	/**Manejo el delete de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Borro Usuario**/
	msg_t msg;
	string id = httpReqParser.getId(hm);
	if (httpReqParser.idOk()) {
		LOG(INFO)<<"Busco "<< id <<" como identificador";
		DBtuple userId(id+"_id");
		bool ok=DB->get(userId);
		if(ok){
			LOG(INFO)<<"Elimino "<< id <<" como usuario";
			//Va a eliminar un usuario en el Shared
			msg_t  response = sharedClient->deleteUser(userId.value);
			msg.status = response.status;
			msg.body = response.body;
		}else{
			LOG(WARNING)<<"Not success";
			msg=this->badRequest("Not success");
		}
	} else {
		LOG(WARNING)<<"Not success";
		msg=this->badRequest("Not success");
	}
	return msg;
}
msg_t HandlerUsers::handleMsg(struct http_message *hm){
	if((httpReqParser.methodType(hm)!=POST)&&(!validateToken(hm))){
		return unathorized();
	}
	return handle(hm);
}

HandlerUsers::~HandlerUsers() {
	/**Destruyo el handler de users**/
}

