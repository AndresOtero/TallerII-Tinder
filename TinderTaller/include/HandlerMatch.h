/*
 * HandlerMatch.h
 *
 *  Created on: 19 de abr. de 2016
 *      Author: andres
 */
#include "HandlerInterface.h"
#include "CandidateService.h"
#ifndef SRC_HANDLERMATCH_H_
#define SRC_HANDLERMATCH_H_

class HandlerMatch: public HandlerInterface {

	public:
		HandlerMatch(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificatorInterface> tokenAuthentificator,shared_ptr<SharedClient> sharedClient);
		virtual ~HandlerMatch();
	private:
		virtual msg_t handlePost(struct http_message *hm);
		virtual msg_t handleGet(struct http_message *hm);
		shared_ptr<CandidateService> candidateService;
};

#endif /* SRC_HANDLERMATCH_H_ */
