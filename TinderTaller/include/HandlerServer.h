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

#ifndef SRC_HANDLERSERVER_H_
#define SRC_HANDLERSERVER_H_
class HandlerServer {

public:
	HandlerServer(const std::string& db_path);
	std::string  handler(struct mg_connection *nc,struct http_message *hm);
	virtual ~HandlerServer();
private:
	std::shared_ptr<DataBase>DB;
	HTTPRequestParser httpReqParser;
};

#endif /* SRC_HANDLERSERVER_H_ */
