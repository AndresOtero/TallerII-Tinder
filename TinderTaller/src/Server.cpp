/*
 * Server.cpp
 *
 *  Created on: 5 de abr. de 2016
 *      Author: andres
 */

#include "Server.h"

shared_ptr<Server> Server::serverInstance = NULL; //Singleton Patron
bool Server::set = false; //Singleton Patron

static const char *s_http_port = "8000";
static int s_sig_num = 0;
static void *s_db_handle = NULL;

Server::Server() {
	/**Creo el server**/
	mg_mgr_init(&mgr, NULL);  //Inicializo el Mongoose manager
	nc = mg_bind(&mgr, s_http_port, Server::staticEvHandler); //Creo la conexion que escucha.
	mg_set_protocol_http_websocket(nc); //Conecta al event handler de http con la conexion.
}

void Server::staticEvHandler(struct mg_connection *nc, int ev, void *ev_data) {
	/**Se encarga de manejar los eventos generados en el server.Es el handler que se le pasa al mongoose y debe ser estatico.**/
	shared_ptr<Server> instance = Server::serverInstance;
	instance->evHandler(nc, ev, ev_data);
}

void Server::evHandler(struct mg_connection *nc, int ev, void *ev_data) {
	/**Se encarga de manejar los eventos generados en el server.**/
	if (!this->isSet()) {
		LOG(FATAL)<<"Server no esta setteado.";
	}
	struct http_message *hm = (struct http_message *) ev_data;
	shared_ptr<Server> server = Server::getServer();
	msg_t msg;
	switch (ev) {
		case MG_EV_HTTP_REQUEST:
				msg = server->handlerServ->handler(hm);
				LOG(INFO)<<(msg.body)<<","<<msg.status;
				mg_printf(nc, "HTTP/1.1 %d\r\n"
						"Transfer-Encoding: chunked\r\n"
						"\r\n", msg.status);
				mg_printf_http_chunk(nc, "%s", msg.body.c_str());
				mg_send_http_chunk(nc, "", 0);

				break;
		default:
			msg.status = BAD_REQUEST;
			break;
	}
}

shared_ptr<Server> Server::getServer() {
	/**Devuelvo la unica instancia de server**/
	if (serverInstance == NULL) {
		shared_ptr<Server> servInst(new Server());
		Server::serverInstance = servInst;
	}
	return serverInstance;
}

bool Server::setServerDB(shared_ptr<DataBase> DB) {
	/**Setea la base de datos en el server, devuelve true si esta bien seteado**/
	shared_ptr<HandlerServer> handlerS(new HandlerServer(DB));
	this->handlerServ = handlerS;
	LOG(INFO)<< "Inicio servidor";
	set = true;
	return isSet();
	}

bool Server::isSet() {
	/**Devuelve true si el server esta setteado.**/
	return set;
}

void Server::runServer() {
	/**Corre el server.**/
	if (isSet()) {
		mg_mgr_poll(&mgr, 1000); // checks all connection for IO readines. Must be called in loop
	} else {
		LOG(FATAL)<<"No se puede correr si este no esta seteado.";
}
}

Server::~Server() {
	/**	Elimina el server**/
	LOG(INFO)<< "Borro el server";
	mg_mgr_free(&mgr);
}

