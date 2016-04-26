/*
 * HandlerChat.h
 *
 *  Created on: 21 de abr. de 2016
 *      Author: andres
 */
#include "HandlerInterface.h"

#ifndef SRC_HANDLERCHAT_H_
#define SRC_HANDLERCHAT_H_
class HandlerChat: public HandlerInterface {
	public:
		HandlerChat(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator);
		virtual ~HandlerChat();
	private:
		virtual msg_t handle(struct http_message *hm);
		msg_t handlePost(struct http_message *hm);
		msg_t handleGet(struct http_message *hm);

};

#endif /* SRC_HANDLERCHAT_H_ */
