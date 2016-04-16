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

#ifndef SRC_HANDLERSERVER_H_
#define SRC_HANDLERSERVER_H_
class HandlerServer {

public:
	HandlerServer(const std::string& db_path);
	msg_t  handler(struct http_message *hm);
	virtual ~HandlerServer();
private:
	msg_t handlerUsers(struct http_message * hm);
	DataBase* DB;
	HTTPRequestParser httpReqParser;
	msg_t badRequest();
};

#endif /* SRC_HANDLERSERVER_H_ */
