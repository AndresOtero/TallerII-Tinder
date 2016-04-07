/*
 * Server.cpp
 *
 *  Created on: 5 de abr. de 2016
 *      Author: andres
 */

#include "Server.h"


static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;
static int s_sig_num = 0;
static void *s_db_handle = NULL;

static const struct mg_str s_get_method = MG_MK_STR("GET");
static const struct mg_str s_put_method = MG_MK_STR("PUT");
static const struct mg_str s_delele_method = MG_MK_STR("DELETE");
static const struct mg_str s_post_method = MG_MK_STR("POST");

static void handle_sum_call(struct mg_connection *nc, struct http_message *hm) {
  char n1[100], n2[100];
  double result;

  /* Get form variables */
  mg_get_http_var(&hm->body, "n1", n1, sizeof(n1));
  mg_get_http_var(&hm->body, "n2", n2, sizeof(n2));

  /* Send headers */
  mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

  /* Compute the result and send it back as a JSON object */
  result = strtod(n1, NULL) + strtod(n2, NULL);
  mg_printf_http_chunk(nc, "{ \"result\": %lf }", result);
  mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
}
static void signal_handler(int sig_num) {
  signal(sig_num, signal_handler);
  s_sig_num = sig_num;
}

static int has_prefix(const struct mg_str *uri, const struct mg_str *prefix) {
  return uri->len > prefix->len && memcmp(uri->p, prefix->p, prefix->len) == 0;
}

static int is_equal(const struct mg_str *s1, const struct mg_str *s2) {
  return s1->len == s2->len && memcmp(s1->p, s2->p, s2->len) == 0;
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  static const struct mg_str api_prefix = MG_MK_STR("/api/v1");
  struct http_message *hm = (struct http_message *) ev_data;
  struct mg_str key;

  switch (ev) {
    case MG_EV_HTTP_REQUEST:
      if (has_prefix(&hm->uri, &api_prefix)) {
        key.p = hm->uri.p + api_prefix.len;
        key.len = hm->uri.len - api_prefix.len;
        LOG(INFO)<<"Got reply:\n%.*s\n", (int) hm->body.len, hm->body.p;
        if (is_equal(&hm->method, &s_get_method)) {
            handle_sum_call(nc, hm);                    /* Handle RESTful call */
        } else if (is_equal(&hm->method, &s_put_method)) {
            handle_sum_call(nc, hm);                    /* Handle RESTful call */
        } else if (is_equal(&hm->method, &s_delele_method)) {
            handle_sum_call(nc, hm);                    /* Handle RESTful call */
        } else if (is_equal(&hm->method, &s_post_method)) {
            handle_sum_call(nc, hm);                    /* Handle RESTful call */
        }else {
          mg_printf(nc, "%s",
                    "HTTP/1.0 501 Not Implemented\r\n"
                    "Content-Length: 0\r\n\r\n");
        }
      } else {
        mg_serve_http(nc, hm, s_http_server_opts); /* Serve static content */
      }
      break;
    default:
      break;
  }
}



Server::Server() {
	// TODO Auto-generated constructor stub
	  mg_mgr_init(&mgr, NULL);
	  nc = mg_bind(&mgr, s_http_port, ev_handler);
	  mg_set_protocol_http_websocket(nc);
	  s_http_server_opts.document_root = "web_root";
	  LOG(INFO)<< "Inicio servidor";
}
void Server::runServer() {
	  /* Run event loop until signal is received */
	    mg_mgr_poll(&mgr, 1000);
}
Server::~Server() {
	  /* Cleanup */
		LOG(INFO)<< "Borro el server";

	  mg_mgr_free(&mgr);
}

