/*
 * HandlerMatch.cpp
 *
 *  Created on: 19 de abr. de 2016
 *      Author: andres
 */

#include "HandlerMatch.h"

HandlerMatch::HandlerMatch(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator,shared_ptr<SharedClient> sharedClient) {
	/**Creo el handler de match**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=MATCH;

	shared_ptr<CandidateService> candidateServiceAux(new CandidateService(DB,sharedClient));

	this->candidateService = candidateServiceAux;
}

msg_t HandlerMatch::handlePost(struct http_message *hm){
	/**Recibo el post de un match y devuelvo un Accepted en caso de exito.**/
	msg_t msg;
	LOG(INFO) << "Se agrega un nuevo match (HandlerMatch - handlePost).";

	string idEmail = getUser(hm);
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string idEmailMatch = val["email"].asString();

	LOG(INFO)<<"Busco "<< idEmail << " y " << idEmailMatch <<" como identificadores";
	DBtuple userId(idEmail+"_id");
	bool ok=DB->get(userId);
	DBtuple userIdMatch(idEmailMatch+"_id");
	bool okMatch=DB->get(userIdMatch);
	if(ok && okMatch){
		StatusCodeMatch rdo = this->candidateService->match(idEmail, idEmailMatch);
		if (rdo == StatusCodeMatch::OK_UPDATE_MATCH){
			//TODO ACA HAY Q INFORMAR AL ANDROID - GOOGLE CLIENT
			msg.change(ACCEPTED, "{\"Mensaje\":\"Se produjo Match con el candidato seleccionado.\"}");
		} else if(rdo == StatusCodeMatch::ERROR_UPDATE_MATCH) {
			LOG(WARNING)<<"Error informando match";
			msg=this->badRequest("{\"Mensaje\":\"Error informando match.\"}");
		} else if(rdo == StatusCodeMatch::OK_UPDATE_CANDIDATE_MATCH){
			msg.change(ACCEPTED, "{\"Mensaje\":\"Se almaceno correctamente el candidato a match seleccionado.\"}");
		} else if(rdo == StatusCodeMatch::ERROR_MATCH_DUPLICATE){
			LOG(WARNING)<<"Error match ya informado.";
			msg=this->badRequest("{\"Mensaje\":\"Error match ya informado.\"}");
		} else {
			LOG(WARNING)<<"Error informando candidato a match";
			msg=this->badRequest("{\"Mensaje\":\"Error informando candidato a match.\"}");
		}
	} else {
		LOG(WARNING)<<"Not success";
		string error = "{\"Mensaje\":\"Id incorrecto: ";
		if(!ok && okMatch){
			error.append(idEmail);
		} else if(ok && !okMatch){
			error.append(idEmailMatch);
		} else {
			error.append(idEmail);
			error.append(" y ");
			error.append(idEmailMatch);
		}
		error.append("\"}");
	    msg=this->badRequest(error);
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
			msg=this->badRequest("{\"Mensaje\":\"Excede limite diario de busqueda de candidatos.\"}");
		} else {
			string candidatesJson = jsonParse.getCandidatesJson(searchCandidate.candidates);
			LOG(DEBUG) << "Candidatos a match: " << candidatesJson << endl;
			msg.change(OK, candidatesJson);
		}
	}
	else{
		LOG(WARNING)<<"Not success";
		msg=this->badRequest("{\"Mensaje\":\"Id incorrecto.\"}");
	}

	return msg;
}

HandlerMatch::~HandlerMatch() {
	/**Destruyo el handler de Match**/

}

