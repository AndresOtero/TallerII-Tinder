/*
 * HandlerMatch.cpp
 *
 *  Created on: 19 de abr. de 2016
 *      Author: andres
 */

#include "HandlerMatch.h"

HandlerMatch::HandlerMatch(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator) {
	/**Creo el handler de match**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=MATCH;

	shared_ptr<CandidateService> candidateServiceAux(new CandidateService(DB));

	this->candidateService = candidateServiceAux;
}

msg_t HandlerMatch::handlePost(struct http_message *hm){
	/**Recibo el post de un match y devuelvo un Accepted en caso de exito.**/
	msg_t msg;
	LOG(INFO) << "Se agrega un nuevo match (HandlerMatch - handlePost).";

	string idEmail = getUser(hm);
	string idEmailMatch = httpReqParser.getId(hm);

	LOG(INFO)<<"Busco "<< idEmail << " y " << idEmailMatch <<" como identificadores";
	DBtuple userId(idEmail+"_id");
	bool ok=DB->get(userId);
	DBtuple userIdMatch(idEmailMatch+"_id");
	bool okMatch=DB->get(userIdMatch);
	if(ok && okMatch){
		StatusCodeMatch rdo = this->candidateService->match(idEmail, idEmailMatch);
		if (rdo == StatusCodeMatch::OK_UPDATE_MATCH){
			//TODO ACA HAY Q INFORMAR AL ANDROID - GOOGLE CLIENT
			msg.change(ACCEPTED, "Posted maych");
		} else {
			LOG(WARNING)<<"Error informando match";
			msg=this->badRequest("Error informando match");
		}
	} else {
		LOG(WARNING)<<"Not success";
	    msg=this->badRequest("Id incorrecto");
	}

	return msg;
}

msg_t HandlerMatch::handleGet(struct http_message *hm){
	/**Recibo el get de los candidatos a match y devuelvo un Ok en caso de exito.**/
	msg_t msg;
	LOG(INFO) << "Busco candidatos a match (HandlerMatch - handleGet).";

	string idEmail = getUser(hm);

	LOG(INFO)<<"Busco "<< idEmail <<" como identificador";
	DBtuple userId(idEmail+"_id");
	bool ok=DB->get(userId);
	if(ok){
		LOG(INFO)<<"Id:  "<< userId.value;
		search_candidate_t searchCandidate = this->candidateService->searchCandidate(idEmail);
		if(searchCandidate.status == StatusCodeMatch::ERROR_LIMIT_DAILY){
			LOG(WARNING)<<"Excede limite diario de busqueda de candidatos.";
			msg=this->badRequest("Excede limite diario de busqueda de candidatos.");
		} else {
			string candidatesJson = jsonParse.getCandidatesJson(searchCandidate.candidates);
			LOG(DEBUG) << "Candidatos a match: " << candidatesJson << endl;
			msg.change(OK, candidatesJson);
		}
	}
	else{
		LOG(WARNING)<<"Not success";
		msg=this->badRequest("Id incorrecto");
	}

	return msg;
}

HandlerMatch::~HandlerMatch() {
	/**Destruyo el handler de Match**/

}

