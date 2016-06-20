/*
 * HandlerChat.h
 *
 *  Created on: 21 de abr. de 2016
 *      Author: andres
 */

#ifndef SRC_HANDLERCHAT_H_
#define SRC_HANDLERCHAT_H_
#include "HandlerInterface.h"
#include "SharedClient.h"
#include "HTTPRequestParser.h"
#include "GcmClient.h"
const size_t CANT_MESSAGES=10;
class HandlerChat: public HandlerInterface {
	public:
		HandlerChat(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificatorInterface> tokenAuthentificator,shared_ptr<SharedClient> sharedClient,shared_ptr<GcmClient> gcmClient);
		virtual ~HandlerChat();
	private:
		shared_ptr<SharedClient> sharedClient;
		shared_ptr<GcmClient> gcmClient;
		virtual msg_t handlePost(struct http_message *hm);
		virtual msg_t handleGet(struct http_message *hm);
		vector<string> getChatsId(struct http_message *hm);
		Json::Value getChatsIdValue(struct http_message *hm);
		msg_t handleGetAll(struct http_message *hm);
		msg_t handleGetChat(struct http_message *hm);
		Json::Value getChatsIdValueFromDestinatario(string destinatario);
		vector<string> getChatsIdFromDestinatario(string destinatario);
		bool  saveUserChatId(string user,string otherUser,string id);
		string getChatId(string remitente,string destinatario);
		Json::Value  saveNewMessage(string chatId,string  remitente,string message);
		bool saveNewChat(string chatId,string  remitente,string destinatario);
		Json::Value getChatHeader(string user,string chatString,string chatId);
		string readChat(string chat,string user,string messageId,string conversationId);

};

#endif /* SRC_HANDLERCHAT_H_ */
