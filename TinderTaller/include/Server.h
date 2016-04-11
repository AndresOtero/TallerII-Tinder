/*
 * Server.h
 *
 *  Created on: 3 de abr. de 2016
 *      Author: andres
 */
#include "mongoose.h"
#include "easylogging++.h"

#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

class Server {
	  struct mg_mgr mgr;// is an event manager that holds all active connections
	  struct mg_connection *nc;//describes a connection
public:
	Server();
	void runServer();
	virtual ~Server();
};

#endif /* SRC_SERVER_H_ */
