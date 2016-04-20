/*
 * HandlerInterface.h
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */
#include "HTTPRequest.h"
#include "mongoose.h"
#include "HTTPRequestParser.h"
#include "JsonParser.h"
#include "DataBase.h"
#ifndef SRC_HANDLERINTERFACE_H_
#define SRC_HANDLERINTERFACE_H_

class HandlerInterface {
	public:
		virtual ~HandlerInterface();
		virtual msg_t handle(struct http_message *hm,shared_ptr<DataBase> db)=0;
	protected:
		HTTPRequestParser httpReqParser;
		JsonParser jsonParse;

};

#endif /* SRC_HANDLERINTERFACE_H_ */
