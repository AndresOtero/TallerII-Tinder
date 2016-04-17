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
msg_t HandlerUsers::handle(struct http_message *hm){
	MethodType methodT=httpReqParser.methodType(hm);
		msg_t msg;
		Json::Value val= jsonParse.stringToValue(hm->body.p);
		int a =jsonParse.getIntFromValue(val,"users");
		std::ostringstream stringStream;
		switch(methodT){
				case PUT:
					LOG(INFO) << "Entro al put";
					msg.status=OK;
					stringStream <<"{ \"result\":"<< a <<"  }";
					msg.body.append(stringStream.str());
				default:
					msg.status=OK;
		}
		return msg;
}

HandlerUsers::~HandlerUsers() {
	// TODO Auto-generated destructor stub
}

