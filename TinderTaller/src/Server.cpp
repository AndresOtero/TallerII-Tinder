/*
 * Server.cpp
 *
 *  Created on: 5 de abr. de 2016
 *      Author: andres
 */

#include "Server.h"

Server* Server::serverInstance = NULL; //Singleton Patron
bool Server::set = false; //Singleton Patron

static const char *s_http_port = "8000";
static int s_sig_num = 0;
static void *s_db_handle = NULL;


void Server::staticEvHandler(struct mg_connection *nc, int ev, void *ev_data) {
	/**Se encarga de manejar los eventos generados en el server.Es el handler que se le pasa al mongoose y debe ser estatico.**/
	Server* instance = Server::serverInstance;
	instance->evHandler(nc, ev, ev_data);
}

void Server::evHandler(struct mg_connection *nc, int ev, void *ev_data) {
	/**Se encarga de manejar los eventos generados en el server.**/
	if(!this->isSet()){
		LOG(FATAL)<<"Server no esta setteado.";
	}
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
	/**Devuelvo la unica instancia de server**/
	if (serverInstance == NULL) {
		serverInstance=new Server();
	}
	return serverInstance;
}

Server::Server() {
	/**Creo el server**/
	mg_mgr_init(&mgr, NULL);  //Initialize Mongoose manager
	nc = mg_bind(&mgr, s_http_port, Server::staticEvHandler); //Create listening connection.
	mg_set_protocol_http_websocket(nc); //Attach built-in HTTP event handler to the given connection.
	serverInstance=this;
}
bool Server::setServerDB(DataBase* DB) {
	/**Setea la base de datos en el server, devuelve true si esta bien seteado**/
	this->handlerServ=new HandlerServer(DB);
	LOG(INFO)<< "Inicio servidor";
	set=true;
	return isSet();
}
bool Server::isSet() {
	/**Devuelve true si el server esta setteado.**/
	return set;
}
void Server::runServer() {
	/**Corre el server.**/
	mg_mgr_poll(&mgr, 1000); // checks all connection for IO readines. Must be called in loop
}
Server::~Server() {
	/**	Elimina el server**/
	LOG(INFO)<< "Borro el server";
	delete handlerServ;
	mg_mgr_free(&mgr);
}

