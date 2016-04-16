
#include "../include/mongoose.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#define ELPP_THREAD_SAFE
#include <cstdio>
#include <string>
#include <assert.h>
#include "../include/Client.h"
#include "../include/Server.h"
#include "../include/DataBase.h"
/** Implementacion de server web**/
int logg()
{
	   LOG(INFO) << "My first info log using default logger";

    return 0;
}


int main(int argc,char*  argv[]) {
	Server* server=Server::getServer();
	std::shared_ptr<Client> client(new Client());

	bool continuar=true;
	while(continuar){
		server->runServer();
	}
	/**while(true){
		server->runServer();

	}**/
	delete server;
    return 0;
}
