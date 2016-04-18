/*
 * HandlerUsers.cpp
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */

#include "HandlerUsers.h"

HandlerUsers::HandlerUsers() {
	// TODO Auto-generated constructor stub

}
msg_t HandlerUsers::handle(struct http_message *hm,DataBase* db){
	MethodType methodT=httpReqParser.methodType(hm);
		msg_t msg;
		Json::Value val= jsonParse.stringToValue(hm->body.p);
		string a =jsonParse.getStringFromValue(val["user"],"name");
		DBtuple tp;
		tp.key=a;
		tp.value=hm->body.p;
		//db->put(tp); TODO ERROR NO SE PORQUE
		LOG(INFO)<<"Creo "<<a<<" como usuario";
		std::ostringstream stringStream;
		switch(methodT){
				case POST:
					LOG(INFO) << "Entro al POST";
					msg.status=CREATED;
					stringStream <<"{ \"result\": \""<< a <<" \" }";
					LOG(INFO) << stringStream.str();
					msg.body.append(stringStream.str());
				default:
					msg.status=OK;
		}
		return msg;
}

HandlerUsers::~HandlerUsers() {
	// TODO Auto-generated destructor stub
}

