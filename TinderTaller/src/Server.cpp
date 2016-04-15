/*
 * Server.cpp
 *
 *  Created on: 5 de abr. de 2016
 *      Author: andres
 */

#include "Server.h"

std::shared_ptr<Server> Server::serverInstance = NULL; //Singleton Patron

static const char *s_http_port = "8000";
static int s_sig_num = 0;
static void *s_db_handle = NULL;





void Server::staticEvHandler(struct mg_connection *nc, int ev, void *ev_data) {
	/**Has to be static for mongoose to use it**/
	std::shared_ptr<Server> instance = Server::serverInstance;
	instance->evHandler(nc, ev, ev_data);
}

void Server::evHandler(struct mg_connection *nc, int ev, void *ev_data) {
	struct http_message *hm = (struct http_message *) ev_data;

	switch (ev) {
	case MG_EV_HTTP_REQUEST:
		handlerServ->handler(nc, hm);


		break;
	default:
		break;
	}
}
shared_ptr<Server> Server::getServer() {
	if (serverInstance == NULL) {
		serverInstance = std::make_shared<Server>();
	}
	return serverInstance;
}

Server::Server() {
	mg_mgr_init(&mgr, NULL);  //Initialize Mongoose manager
	nc = mg_bind(&mgr, s_http_port, Server::staticEvHandler); //Create listening connection.
	mg_set_protocol_http_websocket(nc); //Attach built-in HTTP event handler to the given connection.
	std::shared_ptr < HandlerServer > handlerServ = make_shared < HandlerServer
			> ("/tmp/test");
	LOG(INFO)<< "Inicio servidor";
}
void Server::runServer() {
	mg_mgr_poll(&mgr, 1000); // checks all connection for IO readines. Must be called in loop
}
Server::~Server() {
	/* Cleanup */
	LOG(INFO)<< "Borro el server";

	mg_mgr_free(&mgr);
}

