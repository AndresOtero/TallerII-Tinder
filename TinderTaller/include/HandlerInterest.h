/*
 * HandlerInterest.h
 *
 *  Created on: 4 de may. de 2016
 *      Author: andres
 */

#ifndef SRC_HANDLERS_HANDLERINTEREST_H_
#define SRC_HANDLERS_HANDLERINTEREST_H_
#include "HandlerInterface.h"
#include "SharedClient.h"

class HandlerInterest: public HandlerInterface {
public:
	HandlerInterest(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator,shared_ptr<SharedClient> sharedClient);
	virtual ~HandlerInterest();

private:
	shared_ptr<SharedClient> sharedClient;
	virtual msg_t handle(struct http_message *hm);
	msg_t getInterest(struct http_message *hm);
	msg_t postInterest(struct http_message *hm);


};

#endif /* SRC_HANDLERS_HANDLERINTEREST_H_ */
