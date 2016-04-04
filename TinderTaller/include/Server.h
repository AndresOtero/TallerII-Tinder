/*
 * Server.h
 *
 *  Created on: 3 de abr. de 2016
 *      Author: andres
 */
#include "../include/mongoose.h"
#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

class Server {
	  struct mg_mgr mgr;
	  struct mg_connection *nc;
public:
	Server();
	void startServer();
	virtual ~Server();
};

#endif /* SRC_SERVER_H_ */
