/*
 * HandlerServer.h
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */
#include "mongoose.h"
#include <iostream>
#include "DataBase.h"
#include "HTTPRequestParser.h"
#include "HTTPRequest.h"
#include "HandlerUsers.h"
#include "HandlerMatch.h"
#include "HandlerChat.h"
#ifndef SRC_HANDLERSERVER_H_
#define SRC_HANDLERSERVER_H_
class HandlerServer {
	public:
		HandlerServer(shared_ptr<DataBase> DB);
		msg_t  handler(struct http_message *hm);
		virtual ~HandlerServer();
	private:
		vector<shared_ptr<HandlerInterface>> vecHandler;
		shared_ptr<DataBase> DB;
		HTTPRequestParser httpReqParser;
		msg_t badRequest();
};

#endif /* SRC_HANDLERSERVER_H_ */
