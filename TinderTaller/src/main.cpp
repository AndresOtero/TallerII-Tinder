
#include "../include/mongoose.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP
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
	std::shared_ptr<Server> server(new Server());
	std::shared_ptr<Client> client(new Client());

	bool continuar=true;
	while(continuar){
		server->runServer();
		continuar=client->runClient();
	}
	/**while(true){
		server->runServer();

	}**/
    return 0;
}
