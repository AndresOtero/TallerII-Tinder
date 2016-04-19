/*
 * HandlerUsers.cpp
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */

#include "HandlerUsers.h"
string json_example = "{\"holis\" :\"andy\" }";
HandlerUsers::HandlerUsers() {
	// TODO Auto-generated constructor stub

}

bool HandlerUsers::postUser(struct http_message * hm,DataBase* db) {
	Json::Value val= jsonParse.stringToValue(hm->body.p);
	string a =jsonParse.getStringFromValue(val["user"],"name");
	DBtuple tp;
	tp.key=a;
	tp.value=hm->body.p;
	bool ok=db->put(tp);
	if(ok){
		LOG(INFO)<<"Creo "<< a <<" como usuario";
	}else{
		LOG(WARNING)<<"Not success";
	}
	return ok;
}
msg_t HandlerUsers::handle(struct http_message *hm, DataBase* db) {
	MethodType methodT = httpReqParser.methodType(hm);
	msg_t msg;
	bool ok;
	switch (methodT) {
	case POST:
		ok = this->postUser(hm, db);
		if (ok) {
			msg.status = CREATED;
			msg.body.append(json_example);
		} else {
			msg.status = BAD_REQUEST;
			msg.body.append(json_example);
		}
	default:
		msg.status = OK;
	}
	return msg;
}

HandlerUsers::~HandlerUsers() {
	// TODO Auto-generated destructor stub
}

