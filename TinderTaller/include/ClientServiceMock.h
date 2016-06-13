/*
 * ClientServiceMock.h
 *
 *  Created on: Jun 11, 2016
 *      Author: andres
 */
#include "ClientServiceInterface.h"
#ifndef CLIENTSERVICEMOCK_H_
#define CLIENTSERVICEMOCK_H_

class ClientServiceMock: public ClientServiceInterface {
public:
	ClientServiceMock();
	MemoryStruct getClientService(const char * url);
	MemoryStruct postClientService(const char * url, const char * data);
	MemoryStruct postWithAuthorizationClientService(const char * url, const char * data, const char * authorization);
	MemoryStruct putClientService(const char * url, const char * data);
	MemoryStruct deleteClientService(const char * url);
	virtual ~ClientServiceMock();
};

#endif /* CLIENTSERVICEMOCK_H_ */
