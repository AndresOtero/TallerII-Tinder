/*
 * HandlerUsers.h
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */

#ifndef SRC_HANDLERUSERS_H_
#define SRC_HANDLERUSERS_H_

#include "HandlerInterface.h"

class HandlerUsers: public HandlerInterface {
public:
	HandlerUsers();
	virtual msg_t handle(struct http_message *hm,DataBase* db);
	virtual ~HandlerUsers();
};

#endif /* SRC_HANDLERUSERS_H_ */
