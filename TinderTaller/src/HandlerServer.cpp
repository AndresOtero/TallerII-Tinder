/*
 * HandlerServer.cpp
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */

#include "HandlerServer.h"
static const struct mg_str s_get_method = MG_MK_STR("GET");
static const struct mg_str s_put_method = MG_MK_STR("PUT");
static const struct mg_str s_delele_method = MG_MK_STR("DELETE");
static const struct mg_str s_post_method = MG_MK_STR("POST");
static struct mg_serve_http_opts s_http_server_opts;

static bool has_prefix(const struct mg_str *uri, const struct mg_str *prefix) {
	return uri->len > prefix->len && memcmp(uri->p, prefix->p, prefix->len) == 0;
}

static bool is_equal(const struct mg_str *s1, const struct mg_str *s2) {
	return s1->len == s2->len && memcmp(s1->p, s2->p, s2->len) == 0;
}static void handle_sum_call(struct mg_connection *nc, struct http_message *hm) {
	//char n1[100], n2[100];
	//double result;
	//struct json_token  tok[2],*n1,*n2;
	//int tokens_size = sizeof(tok) / sizeof(tok[0]);

	/* Get form variables */
	//mg_get_http_var(&hm->body, "n1", n1, sizeof(n1));
	//mg_get_http_var(&hm->body, "n2", n2, sizeof(n2));
	//int a =parse_json(hm->body.p,hm->body.len , tok ,tokens_size);
	//n1=find_json_token(tok,"n1");
	//n2=find_json_token(tok,"n2");
	mg_printf(nc, "%s",
			"HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	/* Compute the result and send it back as a JSON object */
	//double n1_ = strtod(n1->ptr, NULL);
	//double n2_ = strtod(n2->ptr, NULL);
	//LOG(INFO)<< "3\n";
	//double result=n1_;
	double result = 0;
	mg_printf_http_chunk(nc, "{ \"result\": %lf }", result);
	mg_send_http_chunk(nc, "", 0); /* Send empty chunk, the end of response */
}
/**
 static void signal_handler(int sig_num) {
 signal(sig_num, signal_handler);
 s_sig_num = sig_num;
 }
 **/


HandlerServer::HandlerServer(const std::string& db_path) {
	// Por ahora solo configuro el path , crea una si no existe pero no borra la que existe.
	std::shared_ptr<DataBase> DB=make_shared<DataBase>(db_path,true,false);
}
std::string  HandlerServer::handler(struct mg_connection *nc,struct http_message *hm) {
	struct mg_str key;
	static const struct mg_str api_prefix = MG_MK_STR("/api/v1");
	if (has_prefix(&hm->uri, &api_prefix)) {
			key.p = hm->uri.p + api_prefix.len;
			key.len = hm->uri.len - api_prefix.len;
			LOG(INFO)<< "Got reply: "<<(int) hm->body.len<<","<< hm->body.p<<"\n";
			if (is_equal(&hm->method, &s_get_method)) {
				handle_sum_call(nc, hm); /* Handle RESTful call */
			} else if (is_equal(&hm->method, &s_put_method)) {
				handle_sum_call(nc, hm); /* Handle RESTful call */
			} else if (is_equal(&hm->method, &s_delele_method)) {
				handle_sum_call(nc, hm); /* Handle RESTful call */
			} else if (is_equal(&hm->method, &s_post_method)) {
				handle_sum_call(nc, hm); /* Handle RESTful call */
			} else {
				mg_printf(nc, "%s", "HTTP/1.0 501 Not Implemented\r\n"
						"Content-Length: 0\r\n\r\n");
			}
		} else {
			mg_serve_http(nc, hm, s_http_server_opts); /* Serve static content */
		}
}

HandlerServer::~HandlerServer() {

}

