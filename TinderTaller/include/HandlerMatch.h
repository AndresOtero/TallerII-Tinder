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
		HandlerMatch(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator);
		virtual ~HandlerMatch();
	private:
		virtual msg_t handlePost(struct http_message *hm);
		virtual msg_t handleGet(struct http_message *hm);
};

#endif /* SRC_HANDLERMATCH_H_ */
