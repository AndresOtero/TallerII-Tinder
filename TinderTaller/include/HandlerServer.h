/*
 * HandlerServer.h
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */
#include "mongoose.h"
#include <iostream>

#ifndef SRC_HANDLERSERVER_H_
#define SRC_HANDLERSERVER_H_
class HandlerServer {
public:
	HandlerServer();
	std::string  handler(struct mg_connection *nc,struct http_message *hm);
	virtual ~HandlerServer();
};

#endif /* SRC_HANDLERSERVER_H_ */
