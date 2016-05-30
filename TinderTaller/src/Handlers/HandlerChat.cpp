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

bool HandlerChat::saveNewMessage(string chatId,string  remitente,string message) {
	DBtuple getChat("chat_"+chatId);
	DB->get(getChat);
	Json::Value newMessage;
	newMessage["user"]=remitente;
	newMessage["message"]=message;
	TimeUtils timeUtils;
	newMessage["time"]= timeUtils.timeToString();
	Json::Value chat=jsonParse.stringToValue(getChat.value);
	int newMessageId=chat["message_id"].asInt();
	int messageId=newMessageId+1;
	chat["message_id"]=messageId;
	string messageIdString=to_string(newMessageId);
	chat["Messages"][messageIdString]=newMessage;
	if(chat["User1"].asString()==remitente){
		chat["LastMessage1"]=0;
		chat["LastMessage2"]=1+chat["LastMessage2"].asInt();
	}else{
		chat["LastMessage2"]=0;
		chat["LastMessage1"]=1+chat["LastMessage1"].asInt();
	}
	string saveChat=jsonParse.valueToString(chat);
	getChat.value=saveChat;
	string newMessageString=jsonParse.valueToString(newMessage);
	LOG(INFO)<<"Nuevo Mensaje id:"<< messageIdString<<" mensaje:"<<newMessageString;
	DB->put(getChat);
}

bool HandlerChat::saveNewChat(string chatId,string  remitente,string destinatario) {
	DBtuple putChat("chat_"+chatId);
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
	return DB->put(putChat);
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
	DBtuple getChat("chat_"+chatId);
	bool okGetChat=DB->get(getChat);
	if(!okGetChat){
		this->saveNewChat(chatId,remitente,destinatario);
	}
	this->saveNewMessage(chatId,remitente,mensaje);
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

string HandlerChat::getChatHeader(string user,string chatString){
	Json::Value chat=jsonParse.stringToValue(chatString);
	Json::Value header;
	if(chat["User1"].asString()==user){
		header["Unread"]=chat["LastMessage1"];
		header["User"]=chat["User2"];
	}else{
		header["Unread"]=chat["LastMessage2"];
		header["User"]=chat["User1"];
	}
	int newMessageId=chat["message_id"].asInt();
	header["LastMessage"]=chat["Messages"][to_string(newMessageId-1)];
	header["message_id"]=newMessageId-1;
	string headerString=jsonParse.valueToString(header);
	return headerString;
}
msg_t HandlerChat::handleGetAll(struct http_message *hm){
	msg_t msg;
	Json::Value chats;
	string  user=this->getUser(hm);
	LOG(INFO)<<"Busco todas las conversaciones";
	vector<string> chatsIdVector=this->getChatsId(hm);
	for (auto itr: chatsIdVector){
		DBtuple getChat("chat_"+(itr));
		DB->get(getChat);
		//Habria que mandar 1 pag o algo asi
		chats[itr]=this->getChatHeader(user,getChat.value);
	}
	msg.status=OK;
	msg.body=jsonParse.valueToString(chats);
	return msg;
}
string HandlerChat::readChat(string chatString,string user,string messageId){
	Json::Value chat=jsonParse.stringToValue(chatString);
	Json::Value lastsMessages;
	if(chat["User1"].asString()==user){
		chat["LastMessage1"]=0;
	}
	Json::Value messages=chat["Messages"];
	int messageIdSearch=atoi(messageId.c_str());
	for( Json::ValueIterator itr = messages.begin() ; itr != messages.end() ; itr++ ){
		LOG(INFO)<<"id "<<itr.key().asString();
		int currentMessageId=atoi(itr.key().asString().c_str());
		int min=messageIdSearch-CANT_MESSAGES;
		if((currentMessageId<=messageIdSearch)&&(currentMessageId>=(min))){
			lastsMessages[itr.key().asString()]=(*itr);
		}
	}
	int lastMessageId=messageIdSearch-CANT_MESSAGES;
	if(lastMessageId<0){
		lastMessageId=0;
	}
	lastsMessages["LastMessageId"]=lastMessageId;
	string lastsMessagesString=this->jsonParse.valueToString(lastsMessages);
	return lastsMessagesString;
}
msg_t HandlerChat::handleGetChat(struct http_message *hm){
	msg_t msg;
	string ids=httpReqParser.getId(hm);
	string conversation_id=ids.substr(0, ids.find("-"));
	string message_id=ids.substr( ids.find("-")+1,ids.size());
	string user=this->getUser(hm);
	LOG(INFO)<<"Busco conversacion "<<conversation_id;
	LOG(INFO)<<"Busco mensaje "<<message_id;
	Json::Value chatsIds=this->getChatsIdValue(hm);
	if(chatsIds.isMember(conversation_id)){
		msg.status=StatusCode::OK;
		DBtuple getChat("chat_"+conversation_id);
		if(!DB->get(getChat)){
			msg.status=StatusCode::BAD_REQUEST;
		}else{
			msg.status=StatusCode::OK;
			msg.body=this->readChat(getChat.value,user,message_id);
		}
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
	string conversation_id=id.substr(0, id.find("-"));
	if(httpReqParser.isNumber(conversation_id)){
		msg=this->handleGetChat(hm);
	}else{
		msg=this->handleGetAll(hm);
	}
	return msg;
}

