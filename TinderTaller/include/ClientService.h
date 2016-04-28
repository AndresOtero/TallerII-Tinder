/*
 * ClientService.h
 *
 */

#ifndef SRC_CLIENTSERVICE_H_
#define SRC_CLIENTSERVICE_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "easylogging++.h"
#include <curl/curl.h>
#include "ClientUtils.h"

class ClientService {
public:
	ClientService();
	virtual ~ClientService();
	MemoryStruct getClientService(const char * url);
	MemoryStruct postClientService(const char * url, const char * data);
	MemoryStruct putClientService(const char * url, const char * data);
	MemoryStruct deleteClientService(const char * url);
};

#endif /* SRC_CLIENTSERVICE_H_ */
