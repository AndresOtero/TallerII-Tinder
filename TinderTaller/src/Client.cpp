/*
 * Client.cpp
 *
 *  Created on: 3 de abr. de 2016
 *      Author: andres
 */

#include "Client.h"


/* RESTful server host and request URI */
static const char *s_url =
    "http://ajax.googleapis.com/ajax/services/search/web?v=1.0&q=cesanta";

static int s_exit_flag = 0;

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;
  int connect_status;

  switch (ev) {
    case MG_EV_CONNECT:
      connect_status = *(int *) ev_data;
      if (connect_status != 0) {
        printf("Error connecting to %s: %s\n", s_url, strerror(connect_status));
        s_exit_flag = 1;
      }
      break;
    case MG_EV_HTTP_REPLY:
      printf("Got reply:\n%.*s\n", (int) hm->body.len, hm->body.p);
      nc->flags |= MG_F_SEND_AND_CLOSE;
      s_exit_flag = 1;
      break;
    default:
      break;
  }
}
Client::Client() {
	// TODO Auto-generated constructor stub
	  mg_mgr_init(&mgr, NULL);
	  nc = mg_connect_http(&mgr, ev_handler, s_url, NULL, NULL);
	  mg_set_protocol_http_websocket(nc);
}
void Client::startClient() {
	 printf("Starting RESTful client against %s\n", s_url);
	  while (s_exit_flag == 0) {
	    mg_mgr_poll(&mgr, 1000);
	  }
}
Client::~Client() {
	// TODO Auto-generated destructor stub
	  mg_mgr_free(&mgr);
}

