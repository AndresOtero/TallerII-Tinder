/*
 * SharedClient.h
 */

#ifndef SRC_SHAREDCLIENT_H_
#define SRC_SHAREDCLIENT_H_

#include <stdlib.h>
#include <string>
#include "mongoose.h"
#include "easylogging++.h"
#include "HTTPRequest.h"

using namespace std;

class SharedClient {
	public:
		SharedClient();
		virtual ~SharedClient();
		msg_t * getUsers();
		msg_t * setUser(string & user);
		msg_t * getUser(string userId);
		msg_t * updateUser(string userId, string & user);
		msg_t * updateUserPhoto(string userId, string & photo);
		msg_t * deleteUser(string userId);
		msg_t * getInterests();
		msg_t * setInterests(string & interests);

	private:
			bool runGetUsers();
			bool runSetUser();
			bool runGetUser();
			bool runUpdateUser();
			bool runUpdateUserPhoto();
			bool runDeleteUser();
			bool runGetInterests();
			bool runSetInterests();
			msg_t * getResponse();
			struct mg_mgr mgr;
			struct mg_connection *nc;
			int mg_http_common_url_parse_client(const char *url, const char *schema,
			                                    const char *schema_tls, int *use_ssl,
			                                    char **addr, int *port_i,
			                                    const char **path);
};

#endif /* SRC_SHAREDCLIENT_H_ */
