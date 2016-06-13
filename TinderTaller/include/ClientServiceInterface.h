/*
 * ClientServiceInterface.h
 *
 *  Created on: Jun 11, 2016
 *      Author: andres
 */
#include "easylogging++.h"
#include <curl/curl.h>
#include "ClientUtils.h"
#ifndef CLIENTSERVICEINTERFACE_H_
#define CLIENTSERVICEINTERFACE_H_

class ClientServiceInterface {
public:
	virtual MemoryStruct getClientService(const char * url)=0;
	virtual MemoryStruct postClientService(const char * url, const char * data)=0;
	virtual MemoryStruct postWithAuthorizationClientService(const char * url, const char * data, const char * authorization) = 0;
	virtual MemoryStruct putClientService(const char * url, const char * data)=0;
	virtual MemoryStruct deleteClientService(const char * url)=0;
};

#endif /* CLIENTSERVICEINTERFACE_H_ */
