/*
 * Server.h
 *
 *  Created on: 3 de abr. de 2016
 *      Author: andres
 */
#include "mongoose.h"
#include "easylogging++.h"
#include "HandlerServer.h"
#include "HTTPRequest.h"
#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_
using namespace std;
class Server {

public:
	void runServer();
	virtual ~Server();
	static void staticEvHandler(struct mg_connection *nc, int ev, void *ev_data) ;
	static Server* getServer();

	private:
		Server();
		static Server* serverInstance; //Singleton Patron
		struct mg_mgr mgr;// is an event manager that holds all active connections
		struct mg_connection *nc;//describes a connection
		void evHandler(struct mg_connection *nc, int ev, void *ev_data);
		std::shared_ptr<HandlerServer> handlerServ;
	};

#endif /* SRC_SERVER_H_ */
