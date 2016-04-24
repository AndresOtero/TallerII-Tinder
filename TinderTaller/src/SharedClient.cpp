/*
 * SharedClient.cpp
 */

#include "SharedClient.h"

/* URL para conectarse al Shared Server */
static string s_url = "";
static const char *s_url_users = "http://tander.herokuapp.com/users";
static const char *s_url_interests = "http://tander.herokuapp.com/interests";

/* Variables de clase usadas en los handlers cuando se invocan al Shared Server */
static int s_exit_flag = 0;
static msg_t * msg_t_result = NULL;

SharedClient::SharedClient() {
	LOG(INFO)<< "Inicio Shared Cliente";
	nc = NULL;
}

SharedClient::~SharedClient() {
	LOG(INFO)<< "Borro Shared Cliente";
}

static StatusCode getStatusCode(int statusCode){
	StatusCode status = StatusCode::DEFAULT_CODE;

	switch (statusCode) {
		case StatusCode::OK:
			status = StatusCode::OK;
			break;
		case StatusCode::CREATED:
			status = StatusCode::CREATED;
			break;
		case StatusCode::ACCEPTED:
			status = StatusCode::ACCEPTED;
			break;
		case StatusCode::BAD_REQUEST:
			status = StatusCode::BAD_REQUEST;
			break;
		case StatusCode::UNAUTHORIZED:
			status = StatusCode::UNAUTHORIZED;
			break;
		case StatusCode::NOT_FOUND:
			status = StatusCode::NOT_FOUND;
			break;
		case StatusCode::METHOD_NOT_ALLOWED:
			status = StatusCode::METHOD_NOT_ALLOWED;
			break;
		case StatusCode::INTERNAL_ERROR:
			status = StatusCode::INTERNAL_ERROR;
			break;
		case StatusCode::NOT_IMPLEMENTED:
			status = StatusCode::NOT_IMPLEMENTED;
			break;
		default:
			status = StatusCode::DEFAULT_CODE;
			break;
	}

	return status;
}

msg_t * SharedClient::getResponse(){
	msg_t * response = new msg_t();
	response->status = msg_t_result->status;
	response->body = new string();
	response->body->clear();
	response->body->append(msg_t_result->body->c_str());

	delete msg_t_result->body;
	msg_t_result->body = NULL;
	delete msg_t_result;
	msg_t_result = NULL;

	return response;
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
	struct http_message *hm = (struct http_message *) ev_data;
	int connect_status;

	switch (ev) {
		case MG_EV_CONNECT:
			connect_status = *(int *) ev_data;
			if (connect_status != 0) {
				if (msg_t_result == NULL){
					msg_t_result = new msg_t();
				}

				msg_t_result->status = StatusCode::ERROR_CONNECTION;
				msg_t_result->body = new string();
				msg_t_result->body->append("Error connecting to ");
				msg_t_result->body->append(s_url);
				msg_t_result->body->append(": ");
				msg_t_result->body->append(strerror(connect_status));

				LOG(ERROR)<< "Error conectando a " << s_url << ": " << strerror(connect_status);
				s_exit_flag = 1;
			} else {
				LOG(INFO)<< "Conecto a " << s_url << ": " << strerror(connect_status);
			}
			break;
		case MG_EV_HTTP_REPLY:
			nc->flags |= MG_F_SEND_AND_CLOSE;
			LOG(INFO)<< "Obtuvo respuesta de " << s_url;
			LOG(DEBUG)<< "Respuesta - codigo: " << hm->resp_code;
			LOG(DEBUG)<< "Respuesta - body: " << hm->body.p;
			s_exit_flag = 1;
			if (msg_t_result == NULL){
				msg_t_result = new msg_t();
			}
			msg_t_result->status = getStatusCode(hm->resp_code);
			msg_t_result->body = new string();
			msg_t_result->body->append(hm->body.p);
			break;
		default:
			break;
	}
}

bool SharedClient::runGetUsers() {
	mg_mgr_poll(&mgr, 1000);
	return (s_exit_flag == 0);
}

msg_t * SharedClient::getUsers(){
	LOG(INFO)<< "Va a obtener los usuarios (getUsers)";
	mg_mgr_init(&mgr, NULL);
	s_url.clear();
	s_url.append(s_url_users);

	//En el siguiente metodo se setea la cabecera del request con GET.
	nc = mg_connect_http(&mgr, ev_handler, s_url.c_str(), NULL, NULL);
	mg_set_protocol_http_websocket(nc);

	while (msg_t_result == NULL){
		runGetUsers();
	}

	mg_mgr_free(&mgr);

	LOG(INFO)<< "Va a cargar el resultado de obtener los usuarios (getUsers)";
	msg_t * response = getResponse();

	LOG(INFO)<< "FIN de obtener los usuarios (getUsers)";
	return response;
}

bool SharedClient::runSetUser(){
	mg_mgr_poll(&mgr, 1000);
	return (s_exit_flag == 0);
}

msg_t * SharedClient::setUser(string & user){
	LOG(INFO)<< "Va a dar de alta un nuevo usuario (setUser)";
	LOG(DEBUG)<< "El json de alta de usuario es: " << user;
	mg_mgr_init(&mgr, NULL);

	s_url.clear();
	s_url.append(s_url_users);
	const char *extra_headers = "Content-Type: application/json";

	//Como el ultimo parametro no es NULL, asume que es un request del tipo POST
	nc = mg_connect_http(&mgr, ev_handler, s_url.c_str(), extra_headers, user.c_str());
	mg_set_protocol_http_websocket(nc);

	while (msg_t_result == NULL){
		runSetUser();
	}
	mg_mgr_free(&mgr);

	LOG(INFO)<< "Va a cargar el resultado de dar de alta un nuevo usuario (setUser)";
	msg_t * response = getResponse();

	LOG(INFO)<< "FIN de dar de alta un nuevo usuario (setUser)";
	return response;
}

bool SharedClient::runGetUser(){
	mg_mgr_poll(&mgr, 1000);
	return (s_exit_flag == 0);
}

msg_t * SharedClient::getUser(string userId){
	LOG(INFO)<< "Va a obtener un usuario en particular (getUser) - Id: " << userId;
	mg_mgr_init(&mgr, NULL);

	s_url.clear();
	s_url.append(s_url_users);
	s_url.append("/");
	s_url.append(userId.c_str());

	//En el siguiente metodo se setea la cabecera del request con GET.
	nc = mg_connect_http(&mgr, ev_handler, s_url.c_str(), NULL, NULL);
	mg_set_protocol_http_websocket(nc);

	while (msg_t_result == NULL){
		runGetUser();
	}

	mg_mgr_free(&mgr);

	LOG(INFO)<< "Va a cargar el resultado de obtener un usuario en particular (getUser)";
	msg_t * response = getResponse();

	LOG(INFO)<< "FIN de obtener un usuario en particular (getUser)";
	return response;
}

bool SharedClient::runUpdateUser(){
	mg_mgr_poll(&mgr, 1000);
	return (s_exit_flag == 0);
}

int SharedClient::mg_http_common_url_parse_client(const char *url, const char *schema,
                                    const char *schema_tls, int *use_ssl,
                                    char **addr, int *port_i,
                                    const char **path) {
  int addr_len = 0;

  if (memcmp(url, schema, strlen(schema)) == 0) {
    url += strlen(schema);
  } else if (memcmp(url, schema_tls, strlen(schema_tls)) == 0) {
    url += strlen(schema_tls);
    *use_ssl = 1;
#ifndef MG_ENABLE_SSL
    return -1; /* SSL is not enabled, cannot do HTTPS URLs */
#endif
  }

  while (*url != '\0') {
    *addr = (char *) realloc(*addr, addr_len + 5 /* space for port too. */);
    if (*addr == NULL) {
      return -1;
    }
    if (*url == '/') {
      break;
    }
    if (*url == ':') *port_i = addr_len;
    (*addr)[addr_len++] = *url;
    (*addr)[addr_len] = '\0';
    url++;
  }
  if (addr_len == 0) goto cleanup;
  if (*port_i < 0) {
    *port_i = addr_len;
    strcpy(*addr + *port_i, *use_ssl ? ":443" : ":80");
  } else {
    *port_i = -1;
  }

  if (*path == NULL) *path = url;

  if (**path == '\0') *path = "/";

  return 0;

cleanup:
  free(*addr);
  return -1;
}

msg_t * SharedClient::updateUser(string userId, string & user){
	LOG(INFO)<< "Va a actualizar un usuario en particular (updateUser) - Id: " << userId;
	LOG(DEBUG)<< "El json para actualizar un usuarios es: " << user;
	mg_mgr_init(&mgr, NULL);

	s_url.clear();
	s_url.append(s_url_users);
	s_url.append("/");
	s_url.append(userId.c_str());
	const char *extra_headers = "Content-Type: application/json";
	nc = mg_connect_http(&mgr, ev_handler, s_url.c_str(), extra_headers, NULL);

	char *addr = NULL;
	int port_i = -1;
	const char *path = NULL;
	int use_ssl = 0;
	mg_http_common_url_parse_client(s_url.c_str(), "http://", "https://", &use_ssl, &addr,
								   &port_i, &path);
	nc->send_mbuf.buf = NULL;
	nc->send_mbuf.len = 0;
	nc->send_mbuf.size = 0;
	mg_printf(nc, "%s %s HTTP/1.1\r\nHost: %s\r\nContent-Length: %" SIZE_T_FMT
					  "\r\n%s\r\n%s", "PUT", path, addr, strlen(user.c_str()),
				  extra_headers, user.c_str());

	mg_set_protocol_http_websocket(nc);

	while (msg_t_result == NULL){
		runUpdateUser();
	}

	mg_mgr_free(&mgr);

	LOG(INFO)<< "Va a cargar el resultado de actualizar un usuario en particular (updateUser)";
	msg_t * response = getResponse();

	LOG(INFO)<< "FIN de actualizar un usuario en particular (updateUser)";
	return response;
}

bool SharedClient::runUpdateUserPhoto(){
	mg_mgr_poll(&mgr, 1000);
	return (s_exit_flag == 0);
}

msg_t * SharedClient::updateUserPhoto(string userId, string & photo){
	LOG(INFO)<< "Va a actualizar la foto de un usuario en particular (updateUserPhoto) - Id: " << userId;
	LOG(DEBUG)<< "El json para actualizar la foto de un usuarios es: " << photo;
	mg_mgr_init(&mgr, NULL);

	s_url.clear();
	s_url.append(s_url_users);
	s_url.append("/");
	s_url.append(userId.c_str());
	s_url.append("/photo");

	const char *extra_headers = "Content-Type: application/json";
	nc = mg_connect_http(&mgr, ev_handler, s_url.c_str(), extra_headers, NULL);

	char *addr = NULL;
	int port_i = -1;
	const char *path = NULL;
	int use_ssl = 0;
	mg_http_common_url_parse_client(s_url.c_str(), "http://", "https://", &use_ssl, &addr,
								   &port_i, &path);
	nc->send_mbuf.buf = NULL;
	nc->send_mbuf.len = 0;
	nc->send_mbuf.size = 0;
	mg_printf(nc, "%s %s HTTP/1.1\r\nHost: %s\r\nContent-Length: %" SIZE_T_FMT
					  "\r\n%s\r\n%s", "PUT", path, addr, strlen(photo.c_str()),
				  extra_headers, photo.c_str());

	mg_set_protocol_http_websocket(nc);

	while (msg_t_result == NULL){
		runUpdateUserPhoto();
	}

	mg_mgr_free(&mgr);

	LOG(INFO)<< "Va a cargar el resultado de actualizar la foto un usuario en particular (updateUserPhoto)";
	msg_t * response = getResponse();

	LOG(INFO)<< "FIN de actualizar la foto un usuario en particular (updateUserPhoto)";
	return response;
}

bool SharedClient::runDeleteUser(){
	mg_mgr_poll(&mgr, 1000);
	return (s_exit_flag == 0);
}

msg_t * SharedClient::deleteUser(string userId){
	LOG(INFO)<< "Va a eliminar un usuario en particular (deleteUser) - Id: " << userId;
	mg_mgr_init(&mgr, NULL);

	s_url.clear();
	s_url.append(s_url_users);
	s_url.append("/");
	s_url.append(userId.c_str());

	nc = mg_connect_http(&mgr, ev_handler, s_url.c_str(), NULL, NULL);

	char *addr = NULL;
	int port_i = -1;
	const char *path = NULL;
	int use_ssl = 0;
	mg_http_common_url_parse_client(s_url.c_str(), "http://", "https://", &use_ssl, &addr,
								   &port_i, &path);
	nc->send_mbuf.buf = NULL;
	nc->send_mbuf.len = 0;
	nc->send_mbuf.size = 0;
	mg_printf(nc, "%s %s HTTP/1.1\r\nHost: %s", "DELETE", path, addr);

	mg_set_protocol_http_websocket(nc);

	while (msg_t_result == NULL){
		runDeleteUser();
	}

	mg_mgr_free(&mgr);

	LOG(INFO)<< "Va a cargar el resultado de eliminar un usuario en particular (deleteUser)";
	msg_t * response = getResponse();

	LOG(INFO)<< "FIN de eliminar un usuario en particular (deleteUser)";
	return response;
}

bool SharedClient::runGetInterests(){
	mg_mgr_poll(&mgr, 1000);
	return (s_exit_flag == 0);
}

msg_t * SharedClient::getInterests(){
	LOG(INFO)<< "Va a buscar los intereses (getInterests)";
	mg_mgr_init(&mgr, NULL);

	s_url.clear();
	s_url.append(s_url_interests);

	nc = mg_connect_http(&mgr, ev_handler, s_url.c_str(), NULL, NULL);
	mg_set_protocol_http_websocket(nc);

	while (msg_t_result == NULL){
		runGetInterests();
	}

	mg_mgr_free(&mgr);

	LOG(INFO)<< "Va a cargar el resultado de buscar los intereses (getInterests)";
	msg_t * response = getResponse();

	LOG(INFO)<< "FIN de buscar los intereses (getInterests)";
	return response;
}

bool SharedClient::runSetInterests(){
	mg_mgr_poll(&mgr, 1000);
	return (s_exit_flag == 0);
}

msg_t * SharedClient::setInterests(string & interests){
	LOG(INFO)<< "Va a dar de alta nuevo intereses (setInterests)";
    LOG(DEBUG)<< "El json para el alta nuevo intereses es: " << interests;
	mg_mgr_init(&mgr, NULL);

	s_url.clear();
	s_url.append(s_url_interests);
	const char *extra_headers = "Content-Type: application/json\r\nCache-Control: no-cache";

	//Como el ultimo parametro no es NULL, asume que es que es un request del tipo POST
	nc = mg_connect_http(&mgr, ev_handler, s_url.c_str(), extra_headers, interests.c_str());
	mg_set_protocol_http_websocket(nc);

	while (msg_t_result == NULL){
		runSetInterests();
	}

	mg_mgr_free(&mgr);

	LOG(INFO)<< "Va a cargar el resultado de dar de alta nuevo intereses (setInterests)";
	msg_t * response = getResponse();

	LOG(INFO)<< "FIN de dar de alta nuevo intereses (setInterests)";
	return response;
}
