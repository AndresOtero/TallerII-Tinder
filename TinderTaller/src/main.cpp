
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
#include "../include/Server.h"
#include "../include/DataBase.h"

int main(int argc, char* argv[]) {
	if(argc!=2){
		return 1;
	}
	Configuration::setPath(argv[1]);
	Configuration* conf=Configuration::getConfiguration().get();
	bool createIfMissing=conf->getBooleanAttribute("createIfMissing");
	bool deleteAll=conf->getBooleanAttribute("deleteAll");
	shared_ptr<DataBase> db(new DataBase("./DBServer/", createIfMissing, deleteAll));
	shared_ptr<Server> server = Server::getServer();
	server->setServerDB(db);
	bool continuar = true;
	while (continuar && server->isSet()) {
		server->runServer();
	}
	return 0;
}
