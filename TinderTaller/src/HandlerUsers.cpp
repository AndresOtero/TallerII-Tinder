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
		switch(methodT){
				case PUT:
					LOG(INFO) << "Entro al put";
					msg.status=OK;
					msg.body.append("{ \"result\": 2 }");
				default:
					msg.status=OK;
		}
		return msg;
}

HandlerUsers::~HandlerUsers() {
	// TODO Auto-generated destructor stub
}

