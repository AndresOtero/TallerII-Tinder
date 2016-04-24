
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

int main(int argc, char* argv[]) {
	shared_ptr<DataBase> db(new DataBase("./DBServer/", true, false));
	shared_ptr<Server> server = Server::getServer();
	server->setServerDB(db);
	std::shared_ptr<Client> client(new Client());
	bool continuar = true;
	while (continuar && server->isSet()) {
		server->runServer();
	}
	return 0;
}
