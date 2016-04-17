/*
 * Server.cpp
 *
 *  Created on: 5 de abr. de 2016
 *      Author: andres
 */

#include "Server.h"

Server* Server::serverInstance = NULL; //Singleton Patron

static const char *s_http_port = "8000";
static int s_sig_num = 0;
static void *s_db_handle = NULL;


void Server::staticEvHandler(struct mg_connection *nc, int ev, void *ev_data) {
	/**Has to be static for mongoose to use it**/
	Server* instance = Server::serverInstance;
	instance->evHandler(nc, ev, ev_data);
}

void Server::evHandler(struct mg_connection *nc, int ev, void *ev_data) {
	struct http_message *hm = (struct http_message *) ev_data;
	Server* server=Server::getServer();
	msg_t msg;
	switch (ev) {
	case MG_EV_HTTP_REQUEST:
		msg=server->handlerServ->handler(hm);
		LOG(INFO)<<msg.body<<","<<msg.status;
			mg_printf(nc, "HTTP/1.1 %d\r\n"
					"Transfer-Encoding: chunked\r\n"
					"\r\n", msg.status);
		    mg_printf_http_chunk(nc, "%s", msg.body.c_str());
			mg_send_http_chunk(nc, "", 0);
		break;
	default:
		msg.status=BAD_REQUEST;
		break;
	}

}
Server* Server::getServer() {
	if (serverInstance == NULL) {
		serverInstance=new Server();
	}
	return serverInstance;
}

Server::Server() {
	mg_mgr_init(&mgr, NULL);  //Initialize Mongoose manager
	nc = mg_bind(&mgr, s_http_port, Server::staticEvHandler); //Create listening connection.
	mg_set_protocol_http_websocket(nc); //Attach built-in HTTP event handler to the given connection.
	HandlerServer* handlerServ=new HandlerServer("./DB/server");
	serverInstance=this;
	LOG(INFO)<< "Inicio servidor";
}
void Server::runServer() {
	mg_mgr_poll(&mgr, 1000); // checks all connection for IO readines. Must be called in loop
}
Server::~Server() {
	/* Cleanup */
	LOG(INFO)<< "Borro el server";
	delete handlerServ;
	mg_mgr_free(&mgr);
}

