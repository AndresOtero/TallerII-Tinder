/*
 * Client.h
 *
 *  Created on: 3 de abr. de 2016
 *      Author: andres
 */
#include "mongoose.h"

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

class Client {
public:
	Client();
	virtual ~Client();
	bool runClient();
private:
	struct mg_mgr mgr;
	struct mg_connection *nc;
};

#endif /* SRC_CLIENT_H_ */
