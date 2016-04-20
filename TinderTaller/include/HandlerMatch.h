/*
 * HandlerMatch.h
 *
 *  Created on: 19 de abr. de 2016
 *      Author: andres
 */

#ifndef SRC_HANDLERMATCH_H_
#define SRC_HANDLERMATCH_H_

class HandlerMatch: public HandlerInterface {
public:
	HandlerMatch();
	virtual msg_t handle(struct http_message *hm,shared_ptr<DataBase> db);
	virtual ~HandlerMatch();
};

#endif /* SRC_HANDLERMATCH_H_ */
