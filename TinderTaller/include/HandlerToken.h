/*
 * HandlerToken.h
 *
 *  Created on: 1 de may. de 2016
 *      Author: andres
 */
#include "HandlerInterface.h"

#ifndef SRC_HANDLERS_HANDLERTOKEN_H_
#define SRC_HANDLERS_HANDLERTOKEN_H_

class HandlerToken: public HandlerInterface {
public:
	HandlerToken(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator);
	virtual msg_t handleMsg(struct http_message *hm);
	virtual ~HandlerToken();
private:
	virtual msg_t handlePost(struct http_message *hm);
};

#endif /* SRC_HANDLERS_HANDLERTOKEN_H_ */
