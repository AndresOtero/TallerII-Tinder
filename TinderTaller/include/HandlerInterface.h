/*
 * HandlerInterface.h
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */
#include "HTTPRequest.h"
#include "mongoose.h"
#include "HTTPRequestParser.h"
#include "TokenAuthentificatorInterface.h"
#include "TokenAuthentificator.h"
#include "JsonParser.h"
#include "DataBase.h"
#ifndef SRC_HANDLERINTERFACE_H_
#define SRC_HANDLERINTERFACE_H_
const string json_example = "{\"holis\" :\"andy\" }";

class HandlerInterface {
	public:
		virtual ~HandlerInterface()=0;
		virtual msg_t handleMsg(struct http_message *hm);
		virtual bool isHandler(struct http_message *hm);
		virtual bool validateToken(struct http_message *hm);
		virtual bool deleteToken(struct http_message *hm);
		virtual msg_t unathorized();
		virtual msg_t badRequest(string strMsg);

	protected:
		shared_ptr<TokenAuthentificatorInterface> tokenAuthentificator;
		HTTPRequestParser httpReqParser;
		JsonParser jsonParse;
		shared_ptr<DataBase> DB;
		PrefixType prefix;
		virtual msg_t handle(struct http_message *hm);
		virtual msg_t handlePost(struct http_message *hm);
		virtual msg_t handleGet(struct http_message *hm);
		virtual msg_t handlePut(struct http_message *hm);
		virtual msg_t handleDelete(struct http_message *hm);
		string getUser(struct http_message *hm);

		msg_t methodNotAllowed();

};

#endif /* SRC_HANDLERINTERFACE_H_ */
