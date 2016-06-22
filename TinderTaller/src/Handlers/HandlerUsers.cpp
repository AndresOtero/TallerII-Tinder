/*
 * HandlerUsers.cpp
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */
#define TERCERA_POSITION 3
#include "HandlerUsers.h"

HandlerUsers::HandlerUsers(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificatorInterface> tokenAuthentificator,shared_ptr<SharedClient> sharedClient){
	/**Creo el handler de users**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=USERS;
	this->sharedClient=sharedClient;
}

msg_t HandlerUsers::handleGet(struct http_message * hm) {
	/**Manejo el get de user, recibe un mensaje y una base de datos. Devuelve el msg correspondiente**/
	msg_t msg;
	string id = httpReqParser.getId(hm);

	if (httpReqParser.idOk()) {
		LOG(INFO)<<"Busco "<< id <<" como identificador";
		DBtuple userId(id+"_id");
		bool ok=DB->get(userId);
		if(ok){
			LOG(INFO)<<"Id:  "<< userId.value;
			msg = sharedClient->getUser(userId.value);
			Json::Value val= jsonParse.stringToValue(msg.body);
			val=this->loadUserPreferences(val,id);
			msg.body=jsonParse.valueToString(val);
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
	/**Devuelve si el usuario del mensaje existe o no **/
	string mail = jsonParse.getMail(hm->body.p);
	DBtuple key(mail+"_id");
	return DB->get(key);
}

msg_t HandlerUsers::handlePost(struct http_message * hm) {
	/**Manejo el post de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Crea un usuario**/
	/*Candidata a funcion*/
	msg_t msg;
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string pass=jsonParse.removePassword(val);
	string gcm_registration_id=jsonParse.removeGcmId(val);
	if(userExists(hm)){
		msg.change(BAD_REQUEST, "{\"Mensaje\":\"Usuario ya creado\"}");
		return msg;
	}
	val=this->saveUserPreferences(val,val["user"]["email"].asString());
	string user=jsonParse.valueToString(val);
	//Va a dar de alta el usuario en el Shared
	LOG(INFO)<<"Mensaje: "<<user<<"\n";
	msg_t  response = sharedClient->setUser(user);
	LOG(INFO)<<"Respuesta: "<<(response.body)<<","<<response.status<<"\n";
	if (response.status==CREATED){
		string id = jsonParse.getId(response.body);
		string mail = jsonParse.getMail(hm->body.p);
		LOG(INFO)<<"Creo "<< mail <<" como usuario";
		string token=tokenAuthentificator->createJsonToken(mail);
		val["token"]=token;
		val=this->loadUserPreferences(val,mail);
		string  result = jsonParse.valueToString(val);
		LOG(INFO)<<"Result "<< result ;
		DBtuple userId(mail+"_id",id);
		bool okPutId = DB->put(userId);
		DBtuple userPass(mail+"_pass",pass);
		bool okPutPass = DB->put(userPass);
		DBtuple userGcmId(mail+"_gcmId",gcm_registration_id);
		bool okPutGcmId = DB->put(userGcmId);
		Json::Value empty=Json::Value(Json::nullValue);
		DBtuple userChats(mail+"_chats",jsonParse.valueToString(empty));
		bool okPutChats = DB->put(userChats);
		if (!okPutId || !okPutPass || !okPutGcmId || !okPutChats){
			msg.change(INTERNAL_ERROR, "{\"Mensaje\":\"Error en la creacion\"}");
			return msg;
		}
		LOG(INFO)<<"Token: "<<token<<"\n";
		msg.change(response.status, result);
	}else{
		msg=this->badRequest("");
	}
	return msg;
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

Json::Value HandlerUsers::saveUserPreferences(Json::Value val,string userId){
	/**Recibo el mensaje recibido y guardo las preferencias a la hora del match del usuario.**/
	Json::Value preferences;
	Json::Value newInterests=Json::Value(Json::arrayValue);
	Json::Value user=val["user"];
	if(user.isMember("interests")){
		Json::Value interests=user["interests"];
		for( Json::ValueIterator itr = interests.begin() ; itr != interests.end() ; itr++ ){
			if(((*itr)["category"].asString())=="Me interesa conocer"){
				Interest interest;
				interest.changeInterest((*itr)["category"].asString(),(*itr)["value"].asString());
				preferences["preferences"].append(interest.getJsonValue());
			}else{
				newInterests.append(*itr);
			}
		}
		user["interests"]=newInterests;
	}
	DBtuple userPreferenceTp(userId+"_preferences",jsonParse.valueToString(preferences));
 	DB->put(userPreferenceTp);
	val["user"]=user;
	return val;
}


msg_t HandlerUsers::putUserUpdateProfile(struct http_message * hm) {
	/**Manejo el put de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Modifica un usuario**/
	msg_t msg;
	string id = httpReqParser.getId(hm);
	Json::Value userNew = jsonParse.stringToValue(hm->body.p);
	string pass = jsonParse.removePassword(userNew);
	string gcm_registration_id = jsonParse.removeGcmId(userNew);
	LOG(INFO)<<"Pass: "<<pass<<"\n";
	if (httpReqParser.idOk()) {
		LOG(INFO)<<"Busco "<< id <<" como identificador";
		DBtuple userId(id+"_id");
		bool okGet=DB->get(userId);

		if(okGet) {
			if(pass!="") {
				DBtuple userPass(id+"_pass",pass);
				bool okPutPass = DB->put(userPass);
				bool okDelete =this->deleteToken(hm);
				LOG(INFO)<<"Registro Nueva Password ";
			}
			if(gcm_registration_id!="") {
				DBtuple userGcmId(id+"_gcmId",gcm_registration_id);
				bool okPutGcmId = DB->put(userGcmId);
				LOG(INFO)<<"Registro Nuevo GCM Id ";
			}
			msg_t msgGet = sharedClient->getUser(userId.value);
			Json::Value userOld=jsonParse.stringToValue(msgGet.body);
			Json::Value val=jsonParse.replaceNewUserInOldUser(userNew,userOld);
			LOG(INFO)<<"Modifico "<< id <<" como usuario";
			LOG(INFO)<<"Modifico "<< userId.value <<" como id_usuario";
			val=this->saveUserPreferences(val,id);
			//Va a actualizar un usuario en el Shared
			string userNew=jsonParse.valueToString(val);
			msg_t response = sharedClient->updateUser(userId.value, userNew);
			msg.status = response.status;
			msg.body = "";//response.body;
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

msg_t HandlerUsers::putUserUpdatePhoto(struct http_message * hm) {
	/**Manejo el put de user, recibe un mensaje y una base de datos.Devuelve el msg correspondiente.Modifica un usuario**/
	msg_t msg;
	LOG(INFO)<<"Modificar Foto";
	string id = httpReqParser.getId(hm);
	if (httpReqParser.idOk()) {
		LOG(INFO)<<"Busco "<< id <<" como identificador";
		DBtuple userId(id+"_id");
		bool ok=DB->get(userId);
		if(ok){
			LOG(INFO)<<"Modifico la foto "<< id <<" como usuario";
			LOG(INFO)<<"Modifico  la foto "<< userId.value <<" como id_usuario";
			//Va a actualizar un usuario en el Shared
			string photo = "";
			photo.append(jsonParse.parseBody(hm->body.p));
			msg = sharedClient->updateUserPhoto(userId.value, photo);
			if(msg.body=="Bad Request\n"){
				msg=this->badRequest("Bad Photo");
			}
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
		bool okGetId = DB->get(userId);
		DBtuple userPass(id+"_pass");
		bool okDeletePass = DB->delete_(userPass);
		bool okDeleteUser=DB->delete_(userId);
		DBtuple userGcmId(id+"_gcmId");
		bool okDeleteGcmId = DB->delete_(userGcmId);
		DBtuple userChats(id+"_chats");
		bool okDeleteChats = DB->delete_(userChats);
		bool okDeleteToken=this->deleteToken(hm);
		if(okDeleteUser&&okDeleteToken&&okDeletePass&&okGetId&&okDeleteChats&&okDeleteGcmId){
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
	/**Valida el token del mensaje excepto que sea un POST**/
	if((httpReqParser.methodType(hm)!=POST)&&(!validateToken(hm))){
		return unathorized();
	}
	return handle(hm);
}

HandlerUsers::~HandlerUsers() {
	/**Destruyo el handler de users**/
}

