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
#include "ClientServiceInterface.h"

class ClientService : public ClientServiceInterface {
	public:
		ClientService();
		virtual ~ClientService();
		MemoryStruct getClientService(const char * url);
		MemoryStruct postClientService(const char * url, const char * data);
		MemoryStruct postWithAuthorizationClientService(const char * url, const char * data, const char * authorization);
		MemoryStruct putClientService(const char * url, const char * data);
		MemoryStruct deleteClientService(const char * url);
	private:
		MemoryStruct postBaseClientService(const char * url, const char * data, const char * authorization);
};

#endif /* SRC_CLIENTSERVICE_H_ */
