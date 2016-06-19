/*
 * SharedClient.h
 */

#ifndef SRC_SHAREDCLIENT_H_
#define SRC_SHAREDCLIENT_H_

#include <stdlib.h>
#include <string>
#include "ClientService.h"
#include "easylogging++.h"
#include "HTTPRequest.h"
#include "GcmClient.h"
using namespace std;

class SharedClient {
public:
	SharedClient(shared_ptr<ClientServiceInterface> clientService);
	virtual ~SharedClient();
	msg_t getUsers();
	msg_t setUser(string & user);
	msg_t getUser(string userId);
	msg_t updateUser(string userId, string & user);
	msg_t updateUserPhoto(string userId, string & photo);
	msg_t deleteUser(string userId);
	msg_t getInterests();
	msg_t setInterests(string & interests);
private:
	shared_ptr<ClientServiceInterface> clientService;
};

#endif /* SRC_SHAREDCLIENT_H_ */
