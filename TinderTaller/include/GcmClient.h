/*
 * GcmClient.h
 *
 *  Created on: Jun 12, 2016
 *      Author: ediaz
 */

#ifndef GCMCLIENT_H_
#define GCMCLIENT_H_

#include "ClientServiceInterface.h"
#include "easylogging++.h"
#include "string.h"
#include "HTTPRequest.h"

using namespace std;

class GcmClient {
public:
	GcmClient(shared_ptr<ClientServiceInterface> clientService);
	virtual ~GcmClient();
	msg_t setNewMatch(string & dataMatch);
	msg_t setNewChat(string & dataChat);
	msg_t setNewRead(string & readMatch);
private:
	shared_ptr<ClientServiceInterface> clientService ;
	msg_t setInGcm(string & data);
};

#endif /* GCMCLIENT_H_ */
