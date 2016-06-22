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
#include "TokenAuthentificatorInterface.h"
class HandlerUsers: public HandlerInterface {
public:
	HandlerUsers(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificatorInterface> tokenAuthentificator,shared_ptr<SharedClient> sharedClient);
	virtual msg_t handleMsg(struct http_message *hm);
	virtual ~HandlerUsers();
private:
	shared_ptr<SharedClient> sharedClient;
	Json::Value saveUserPreferences(Json::Value user,string userId);

	virtual msg_t handlePost(struct http_message *hm);
	virtual msg_t handleGet(struct http_message *hm);
	virtual msg_t handlePut(struct http_message *hm);
	virtual msg_t handleDelete(struct http_message *hm);
	msg_t putUserUpdateProfile(struct http_message * hm);
	msg_t putUserUpdatePhoto(struct http_message * hm);
	bool userExists(struct http_message * hm);
};

#endif /* SRC_HANDLERUSERS_H_ */
