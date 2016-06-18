/*
 * HandlerMatch.h
 *
 *  Created on: 19 de abr. de 2016
 *      Author: andres
 */
#include "HandlerInterface.h"
#include "CandidateService.h"
#include "GcmClient.h"
#ifndef SRC_HANDLERMATCH_H_
#define SRC_HANDLERMATCH_H_

class HandlerMatch: public HandlerInterface {

	public:
		HandlerMatch(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificatorInterface> tokenAuthentificator,shared_ptr<SharedClient> sharedClient,shared_ptr<GcmClient> gcmClient);
		virtual ~HandlerMatch();
	private:
		virtual msg_t handlePost(struct http_message *hm);
		virtual msg_t handleGet(struct http_message *hm);
		shared_ptr<CandidateService> candidateService;
		shared_ptr<GcmClient> gcmClient;
		bool  saveUserChatId(string user,string otherUser,string id);
		bool saveNewChat(string  remitente,string destinatario);
};

#endif /* SRC_HANDLERMATCH_H_ */
