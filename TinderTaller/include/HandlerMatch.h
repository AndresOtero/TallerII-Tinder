/*
 * HandlerMatch.h
 *
 *  Created on: 19 de abr. de 2016
 *      Author: andres
 */
#include "HandlerInterface.h"
#ifndef SRC_HANDLERMATCH_H_
#define SRC_HANDLERMATCH_H_

class HandlerMatch: public HandlerInterface {

	public:
		HandlerMatch(shared_ptr<DataBase> DB);
		virtual msg_t handle(struct http_message *hm);
		msg_t handlePost(struct http_message *hm);
		msg_t handleGet(struct http_message *hm);
		virtual bool isHandler(struct http_message *hm);
		virtual ~HandlerMatch();
};

#endif /* SRC_HANDLERMATCH_H_ */
