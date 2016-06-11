/*
 * SharedClientMock.h
 *
 *  Created on: Jun 9, 2016
 *      Author: andres
 */

#ifndef SHAREDCLIENTMOCK_H_
#define SHAREDCLIENTMOCK_H_

#include <stdlib.h>
#include <string>
#include "easylogging++.h"
#include "HTTPRequest.h"
#include "SharedClient.h"
#include "fakeit.hpp"
using namespace fakeit;
class SharedClientMock: public SharedClient {
public:
	SharedClientMock();
	virtual ~SharedClientMock();
//MOCK_METHOD1(setUser,msg_t(string &user));
};

#endif /* SHAREDCLIENTMOCK_H_ */
