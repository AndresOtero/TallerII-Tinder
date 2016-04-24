/*
 * HandlerUsers.h
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */

#ifndef SRC_HANDLERUSERS_H_
#define SRC_HANDLERUSERS_H_

#include "HandlerInterface.h"
#include "SharedClient.h"

class HandlerUsers: public HandlerInterface {
public:
	HandlerUsers(shared_ptr<DataBase> DB);
	virtual msg_t handle(struct http_message *hm);
	virtual bool isHandler(struct http_message *hm);
	virtual ~HandlerUsers();
private:
	msg_t postUser(struct http_message * hm );
	msg_t getUser(struct http_message * hm);
	msg_t putUser(struct http_message * hm);
	msg_t deleteUser(struct http_message * hm);
	msg_t putUserUpdateProfile(struct http_message * hm);
	msg_t putUserUpdatePhoto(struct http_message * hm);
};

#endif /* SRC_HANDLERUSERS_H_ */
