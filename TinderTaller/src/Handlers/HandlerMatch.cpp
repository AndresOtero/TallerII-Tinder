/*
 * HandlerMatch.cpp
 *
 *  Created on: 19 de abr. de 2016
 *      Author: andres
 */

#include "HandlerMatch.h"

HandlerMatch::HandlerMatch(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificatorInterface> tokenAuthentificator,shared_ptr<SharedClient> sharedClient,shared_ptr<GcmClient> gcmClient) {
	/**Creo el handler de match**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=MATCH;

	shared_ptr<CandidateService> candidateServiceAux(new CandidateService(DB,sharedClient));
	this->candidateService = candidateServiceAux;


	this->gcmClient = gcmClient;
}
/**void HandlerMatch::createChat(struct http_message *hm){

}**/
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
			msg.change(CREATED, "{\"Mensaje\":\"Se produjo Match con el candidato seleccionado.\"}");
			//TODO ACA HAY Q INFORMAR AL ANDROID - GOOGLE CLIENT
			//TODO ESTO DEBERIA DE ESTAR EN UN HILO QUE SE CORRA MIENTRAS LE RESPONDO AL ANDROID DEL MATCH OK
			DBtuple userGcm(idEmail + "_gcmId");
			bool okUserGcm = DB->get(userGcm);
			DBtuple userGcmMatch(idEmailMatch + "_gcmId");
			bool okUserGcmMatch = DB->get(userGcmMatch);
			if(okUserGcm && okUserGcmMatch){
				LOG(INFO) << "Se van a informar los matchs por Gcm (HandlerMatch - handlePost).";
				int chatId = this->saveNewChat(idEmail,idEmailMatch);

				if (chatId == -1){
					LOG(WARNING)<<"Error obteniendo un chat_id para el nuevo match.";
					msg=this->badRequest("{\"Mensaje\":\"Error obteniendo un chat_id para el nuevo match.\"}");

					return msg;
				}

				string matchGcmJsonString;
				LOG(INFO) << "Se informa a "<<idEmailMatch ;
				matchGcmJsonString = jsonParse.getGcmJson(userGcm.value, idEmailMatch, chatId);
				this->gcmClient->setNewMatch(matchGcmJsonString);
				matchGcmJsonString.clear();

				LOG(INFO) << "Se informa a "<<idEmail ;
				matchGcmJsonString = jsonParse.getGcmJson(userGcmMatch.value, idEmail, chatId);
				this->gcmClient->setNewMatch(matchGcmJsonString);
			} else {
				LOG(WARNING)<<"Error buscando los gcm de los usuarios para informar el match.";
				msg=this->badRequest("{\"Mensaje\":\"Error buscando los gcm de los usuarios para informar el match.\"}");
			}
		} else if(rdo == StatusCodeMatch::ERROR_UPDATE_MATCH) {
			LOG(WARNING)<<"Error informando match";
			msg=this->badRequest("{\"Mensaje\":\"Error informando match.\"}");
		} else if(rdo == StatusCodeMatch::OK_UPDATE_CANDIDATE_MATCH){
			msg.change(CREATED, "{\"Mensaje\":\"Se almaceno correctamente el candidato a match seleccionado.\"}");
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

int HandlerMatch::saveNewChat(string  remitente,string destinatario) {
	/**Recibe el remitente , el chat id y el destinatario y guarda el chat en Base de datos.**/
	DBtuple chatId("chat_id");
	DB->get(chatId);
	string id=chatId.value;
	int id_int=atoi(id.c_str())+1;
	chatId.value=to_string(id_int);
	DB->put(chatId);
	this->saveUserChatId(remitente,destinatario,id);
	this->saveUserChatId(destinatario,remitente,id);
	DBtuple putChat("chat_"+id);
	Json::Value newChat;
	newChat["User1"]=remitente;
	newChat["User2"]=destinatario;
	newChat["LastMessage1"]=0;
	newChat["LastMessage2"]=0;
	newChat["message_id"]=0;
	newChat["Messages"]=Json::Value(Json::nullValue);
	string saveChat=jsonParse.valueToString(newChat);
	putChat.value=saveChat;
	LOG(INFO)<<"Nuevo chat"<<saveChat;

	if (DB->put(putChat)){
		return id_int;
	}

	return -1;
}

bool  HandlerMatch::saveUserChatId(string user,string otherUser,string id){
	/**Guarde el chat id de una nueva conversacion en la lista de chats del usuario**/
	DBtuple getUserChatsId(user+"_chats");
	DB->get(getUserChatsId);
	Json::Value jsonUserChatsId=jsonParse.stringToValue(getUserChatsId.value);
	jsonUserChatsId[id]=otherUser;
	string saveUser=jsonParse.valueToString(jsonUserChatsId);
	DBtuple saveUsersChatId(user+"_chats",saveUser);
	return DB->put(saveUsersChatId);
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
			msg.change(StatusCode::ERROR_LIMIT_DAILY_STATUS_CODE, "{\"Mensaje\":\"Excede limite diario de busqueda de candidatos.\"}");
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
