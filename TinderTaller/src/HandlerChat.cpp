/*
 * HandlerChat.cpp
 *
 *  Created on: 21 de abr. de 2016
 *      Author: andres
 */

#include "HandlerChat.h"

HandlerChat::~HandlerChat() {
	// TODO Auto-generated destructor stub
}

HandlerChat::HandlerChat(shared_ptr<DataBase> DB) {
	/**Creo el handler de match**/
	this->DB=DB;
	this->prefix=CHAT;
}
bool HandlerChat::isHandler(struct http_message *hm) {
	/**Creo el handler de users**/
	return (httpReqParser.prefixType(hm)==prefix);
}
msg_t HandlerChat::handle(struct http_message *hm) {
	MethodType methodT = httpReqParser.methodType(hm);
		msg_t msg;
		switch (methodT) {
			case POST:
				LOG(INFO) << "Mando un mensaje";
				msg.change(ACCEPTED,"Posted maych");
				break;
			case GET:
				LOG(INFO) << "Busco un mensaje";
				msg.change(OK,"Get match");
				break;
			default:
				msg.change(METHOD_NOT_ALLOWED,json_example);
				break;
		}
		return msg;
	}
