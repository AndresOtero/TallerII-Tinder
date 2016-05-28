/*
 * HandlerChat.cpp
 *
 *  Created on: 21 de abr. de 2016
 *      Author: andres
 */

#include "HandlerChat.h"
#include <string.h>
#include <vector>
using namespace std;
HandlerChat::~HandlerChat() {
	// TODO Auto-generated destructor stub
}

HandlerChat::HandlerChat(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator) {
	/**Creo el handler de match**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=CHAT;
}

msg_t HandlerChat::handlePost(struct http_message *hm) {
	/**	Recibo el post de un mensaje y devuelvo un accepted si se realizo correctamente**/
	msg_t msg;
	LOG(INFO) << "Obteniendo los datos para guardar el mensaje del chat.";
	Json::Value bodyValue=jsonParse.stringToValue(hm->body.p);
	string  remitente=this->getUser(hm);
	string destinatario=jsonParse.getStringFromValue(bodyValue,"To");
	string mensaje=jsonParse.getStringFromValue(bodyValue,"message");
	LOG(INFO)<< "El mensaje de "<<remitente<<" a "<<destinatario<<" es "<<mensaje;
	string chatId=this->getChatId(remitente,destinatario);
	LOG(INFO)<< "El chat id es  "<<chatId;

	msg.status=OK;
	return msg;
}
bool  HandlerChat::saveUserChatId(string user,string otherUser,string id){
	DBtuple getUserChatsId(user+"_chats");
	DB->get(getUserChatsId);
	Json::Value jsonUserChatsId=jsonParse.stringToValue(getUserChatsId.value);
	jsonUserChatsId[id]=otherUser;
	string saveUser=jsonParse.valueToString(jsonUserChatsId);
	DBtuple saveUsersChatId(user+"_chats",saveUser);
	return DB->put(saveUsersChatId);
}
string HandlerChat::getChatId(string remitente,string destinatario){
	Json::Value chatsId=getChatsIdValueFromDestinatario(destinatario);
	string id="";
	for( Json::ValueIterator itr = chatsId.begin() ; itr != chatsId.end() ; itr++ ){
		if((*itr).asString()==remitente){
			id=itr.key().asString();
		}
	}
	if(id==""){//Si no existe
		DBtuple chatId("chat_id");
		DB->get(chatId);
		id=chatId.value;
		int id_int=atoi(id.c_str())+1;
		chatId.value=to_string(id_int);
		DB->put(chatId);
		this->saveUserChatId(remitente,destinatario,id);
		this->saveUserChatId(destinatario,remitente,id);
	}
	return id;
}
Json::Value HandlerChat::getChatsIdValueFromDestinatario(string destinatario){
	DBtuple getChatsIds(destinatario+"_chats");
	DB->get(getChatsIds);
	Json::Value chats;
	Json::Value chatsIds=jsonParse.stringToValue(getChatsIds.value);
	return chatsIds;
}
Json::Value HandlerChat::getChatsIdValue(struct http_message *hm){
	string user=this->getUser(hm);
	return this->getChatsIdValueFromDestinatario(user);
}
vector<string> HandlerChat::getChatsId(struct http_message *hm){
	Json::Value chatsIds=this->getChatsIdValue(hm);
	vector<string> chatsIdVector=jsonParse.getKeyVectorFromValue(chatsIds);
	return chatsIdVector;
}
vector<string> HandlerChat::getChatsIdFromDestinatario(string destinatario){
	Json::Value chatsIds=this->getChatsIdValueFromDestinatario(destinatario);
	vector<string> chatsIdVector=jsonParse.getKeyVectorFromValue(chatsIds);
	return chatsIdVector;
}
msg_t HandlerChat::handleGetAll(struct http_message *hm){
	msg_t msg;
	Json::Value chats;
	LOG(INFO)<<"Busco todas las conversaciones";
	vector<string> chatsIdVector=this->getChatsId(hm);
	for (auto itr: chatsIdVector){
		DBtuple getChat((itr));
		DB->get(getChat);
		//Habria que mandar 1 pag o algo asi
		chats[itr]=getChat.value;
	}
	msg.status=OK;
	msg.body=jsonParse.valueToString(chats);
	return msg;
}
msg_t HandlerChat::handleGetChat(struct http_message *hm){
	msg_t msg;
	string id=httpReqParser.getId(hm);
	LOG(INFO)<<"Busco conversacion"<<id;
	Json::Value chatsIds=this->getChatsIdValue(hm);
	if(chatsIds.isMember(id)){
		msg.status=StatusCode::NOT_IMPLEMENTED;
	}else{
		msg.status=StatusCode::UNAUTHORIZED;
	}

	return msg;
}
msg_t HandlerChat::handleGet(struct http_message *hm) {
	/**	Recibo el post de un mensaje y devuelvo un accepted si se realizo correctamente**/
	msg_t msg;
	LOG(INFO) << "Obteniendo los datos para devolver el mensaje.";
	string id=httpReqParser.getId(hm);
	if(httpReqParser.isNumber(id)){
		msg=this->handleGetChat(hm);
	}else{
		msg=this->handleGetAll(hm);
	}
	return msg;
}

