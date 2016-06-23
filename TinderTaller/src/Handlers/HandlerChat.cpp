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

HandlerChat::HandlerChat(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificatorInterface> tokenAuthentificator,shared_ptr<SharedClient> sharedClient,shared_ptr<GcmClient> gcmClient) {
	/**Creo el handler de match**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=CHAT;
	this->sharedClient= sharedClient;
	this->gcmClient = gcmClient;
	DBtuple chatId("chat_id");
	if(!DB->get(chatId)){
		chatId.value="0";
		DB->put(chatId);
	}
}

Json::Value HandlerChat::saveNewMessage(string chatId,string  remitente,string message) {
	/**Recibe el mensaje el remitente y el chat id y lo guarda en Base de datos.**/
	DBtuple getChat("chat_"+chatId);
	DB->get(getChat);
	Json::Value newMessage;
	newMessage["user"]=remitente;
	newMessage["message"]=message;
	TimeUtils timeUtils;
	newMessage["time"]= timeUtils.unixTimeToString();
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
	newMessage["message_id"]=newMessageId;
	return newMessage;
}

/**
msg_t HandlerChat::seenChat(struct http_message *hm){
	vector<string> chatsId=getChatsId(hm);
	string body=jsonParse.stringToValue(hm->body.p);
	if (std::find(chatsId.begin(), chatsId.end(), "abc") != v.end())

}**/
msg_t HandlerChat::handlePost(struct http_message *hm) {
	/**	Recibo el post de un mensaje y devuelvo un Ok si se realizo correctamente**/
	msg_t msg;
	std::vector<std::string> vec = httpReqParser.parsePrefix(hm);
	if (vec.size() >= 3) {
		if (vec[2] == "read") {
			return this->postRead(hm);
		}
	}
	LOG(INFO)<< "Obteniendo los datos para guardar el mensaje del chat.";
	//string visto=httpReqParser.parsePrefix(hm)[2];
	/**if(visto=="visto"){
		return seenChat(hm);
	}**/
	string body=jsonParse.parseBody(hm->body.p);
	Json::Value bodyValue=jsonParse.stringToValue(body);
	string remitente=this->getUser(hm);
	string destinatario=jsonParse.getStringFromValue(bodyValue,"To");
	string mensaje=jsonParse.getStringFromValue(bodyValue,"message");
	LOG(INFO)<< "El mensaje de "<<remitente<<" a "<<destinatario<<" es "<<mensaje;
	string chatId=this->getChatId(remitente,destinatario);
	if(chatId==""){
		msg.change(StatusCode::FORBIDDEN,"Usted no tiene una conversacion con este usuario");
		return msg;
	}
	LOG(INFO)<< "El chat id es  "<<chatId;
	DBtuple getChat("chat_"+chatId);
	bool okGetChat=DB->get(getChat);
	if(!okGetChat){
		msg.change(StatusCode::INTERNAL_ERROR,"Usted no tiene una conversacion con este usuario");
		return msg;	}
	Json::Value newMessage=this->saveNewMessage(chatId,remitente,mensaje);
	DBtuple userToken("token_"+destinatario);
	bool okUserToken = DB->get(userToken);
	if(okUserToken){
		DBtuple getGcmId(destinatario+"_gcmId");
		bool okGetGcm=DB->get(getGcmId);
		Json::Value PushNotification;
		PushNotification["to"]=getGcmId.value;
		Json::Value Notification;
		Notification["title"]=("Nuevo mensaje de "+remitente);
		Notification["body"]=(mensaje);
		PushNotification["notification"]=Notification;
		Json::Value Data;
		Data["type"]="2";
		Data["chat_room_id"]=chatId;
		Data["message_id"]=newMessage["message_id"];
		Data["message"]=mensaje;
		Data["created_at"]=newMessage["time"];
		PushNotification["data"]=Data;
		string jsonNotification=jsonParse.valueToString(PushNotification);
		this->gcmClient->setNewChat(jsonNotification);
	}
	msg.status=OK;
	return msg;
}

string HandlerChat::getChatId(string remitente,string destinatario){
	/**Busca el chat id de la conversacion sino existe lo crea.**/
	Json::Value chatsId=getChatsIdValueFromDestinatario(destinatario);
	string id="";
	for( Json::ValueIterator itr = chatsId.begin() ; itr != chatsId.end() ; itr++ ){
		if((*itr).asString()==remitente){
			id=itr.key().asString();
		}
	}
	return id;
}

Json::Value HandlerChat::getChatsIdValueFromDestinatario(string destinatario){
	/**Busco la lista de chatsid del destinatario**/
	DBtuple getChatsIds(destinatario+"_chats");
	DB->get(getChatsIds);
	Json::Value chats;
	Json::Value chatsIds=jsonParse.stringToValue(getChatsIds.value);
	return chatsIds;
}
msg_t HandlerChat::postRead(struct http_message *hm){
	LOG(INFO)<<"Post read";
	msg_t msg;
	string user=this->getUser(hm);
	string bodyString=jsonParse.parseBody(hm->body.p);
	LOG(INFO)<<"El mensaje recibido es "<<bodyString;
	Json::Value body = jsonParse.stringToValue(bodyString);
	string messageId=body["message_id"].asString();
	string chatId=body["chatroom_id"].asString();
	DBtuple getChat("chat_"+(chatId));
	DB->get(getChat);
	Json::Value chat=jsonParse.stringToValue(getChat.value);
	int lastMessageId=chat["message_id"].asInt();
	int lastMessageIdRead=atoi(messageId.c_str());
	string otherUser;
	if(chat["User1"].asString()==user){
		otherUser=chat["User2"].asString();
		if((lastMessageId-1)>=(lastMessageIdRead)){
			chat["LastMessage1"]=lastMessageId-1-lastMessageIdRead;
		}
	}else{
		otherUser=chat["User1"].asString();
		if((lastMessageId-1)>=(lastMessageIdRead)){
			chat["LastMessage2"]=lastMessageId-1-lastMessageIdRead;
		}
	}
	DBtuple putChat("chat_"+(chatId),jsonParse.valueToString(chat));
	DB->put(putChat);
	DBtuple userToken("token_"+otherUser);
	bool okUserToken = DB->get(userToken);
	if(okUserToken){
		DBtuple getGcmId(otherUser+"_gcmId");
		bool okGetGcm=DB->get(getGcmId);
		Json::Value PushNotification;
		PushNotification["to"]=getGcmId.value;
		body["type"]="3";
		PushNotification["data"]=body;
		string jsonNotification=jsonParse.valueToString(PushNotification);
		LOG(INFO)<<"Mando a"<<otherUser <<" mensaje enviado es "<<jsonNotification;
		msg=this->gcmClient->setNewRead(jsonNotification);
	} else {
		msg.status=StatusCode::ACCEPTED;
	}
	return msg;
}

Json::Value HandlerChat::getChatsIdValue(struct http_message *hm){
	/**Busca la lista de chatsid del destinatario dado el hm**/
	string user=this->getUser(hm);
	return this->getChatsIdValueFromDestinatario(user);
}

vector<string> HandlerChat::getChatsId(struct http_message *hm){
	/**Busca la lista de chatsid del destinatario dado el hm y devuelvo la lista de strings con los chatsId**/
	Json::Value chatsIds=this->getChatsIdValue(hm);
	vector<string> chatsIdVector=jsonParse.getKeyVectorFromValue(chatsIds);
	return chatsIdVector;
}


Json::Value HandlerChat::getChatHeader(string user,string chatId){
	/**Busca el chat header, devuelvo el header con el ultimo mensaje, con el ultimo mensajeId mandado ,
	 * con la cantidad de mensajes sin leer y con el otro usario en la conversacion. **/
	DBtuple getChat("chat_"+(chatId));
	DB->get(getChat);
	Json::Value chat=jsonParse.stringToValue(getChat.value);
	LOG(DEBUG)<<getChat.value;
	Json::Value header;
	if(chat["User1"].asString()==user){
		header["Unread"]=chat["LastMessage1"];
		header["User"]=chat["User2"];
	}else{
		header["Unread"]=chat["LastMessage2"];
		header["User"]=chat["User1"];
	}
	string mail = header["User"].asString();
	DBtuple tpId(mail+"_id");
	bool okId=DB->get(tpId);
	msg_t msgGet = sharedClient->getUser(tpId.value);
	Json::Value jsonData=jsonParse.stringToValue(msgGet.body);
	header["user"]= jsonParse.getUserValueJson(jsonData["user"]);
	int newMessageId=chat["message_id"].asInt();
	if(chat["Messages"].isMember(to_string(newMessageId-1))){
		header["LastMessage"]=chat["Messages"][to_string(newMessageId-1)];
	}
	header["message_id"]=newMessageId-1;
	header["chatroom_id"]=chatId;
	string headerString=jsonParse.valueToString(header);
	LOG(DEBUG)<<headerString;

	return header;
}

msg_t HandlerChat::handleGetAll(struct http_message *hm){
	/**Busca los headers de todos los mensajes de los usuarios.**/
	msg_t msg;
	Json::Value headers;
	Json::Value chats= Json::Value(Json::arrayValue);;
	string  user=this->getUser(hm);
	LOG(INFO)<<"Busco todas las conversaciones";
	vector<string> chatsIdVector=this->getChatsId(hm);
	for (auto itr: chatsIdVector){
		chats.append(this->getChatHeader(user,itr));
	}
	headers["chats"]=chats;
	msg.status=OK;
	string result=jsonParse.valueToString(headers);
	msg.body=result;
	return msg;
}
string HandlerChat::readChat(string chatString,string user,string messageId,string conversationId){
	/**Leo la CANT_MENSAJES desde mensajeId del chat desde la vista del usuario.Actualiza los estados con los
	 * ultimos mensajes leidos en la conversacion.**/
	Json::Value chat=jsonParse.stringToValue(chatString);
	Json::Value lastsMessages;
	Json::Value lastsMessagesMsg= Json::Value(Json::arrayValue);
	LOG(DEBUG)<<chatString;
	int lastMessageRead;
	int lastMessageId=chat["message_id"].asInt();
	if(chat["User1"].asString()==user){
		lastMessageRead=chat["LastMessage2"].asInt();
		chat["LastMessage1"]=0;
	}else{
		lastMessageRead=chat["LastMessage1"].asInt();
		chat["LastMessage2"]=0;
	}
	Json::Value messages=chat["Messages"];
	int messageIdSearch=atoi(messageId.c_str());
	for( Json::ValueIterator itr = messages.begin() ; itr != messages.end() ; itr++ ){
		LOG(INFO)<<"id "<<itr.key().asString();
		int currentMessageId=atoi(itr.key().asString().c_str());
		int min=messageIdSearch-CANT_MESSAGES;
		if((currentMessageId<=messageIdSearch)&&(currentMessageId>=(min))){
			Json::Value Message=*itr;
			if(currentMessageId>=(lastMessageId-lastMessageRead)){
				Message["status"]="D";
			}else{
				Message["status"]="R";
			}
			Message["message_id"]=itr.key().asString();
			lastsMessagesMsg.append(Message);
		}
	}
	lastsMessages["messages"]=lastsMessagesMsg;
	int bottomMessageId=messageIdSearch-CANT_MESSAGES;
	if(bottomMessageId<0){
		bottomMessageId=0;
	}
	lastsMessages["LastMessageId"]=bottomMessageId;
	string lastsMessagesString=this->jsonParse.valueToString(lastsMessages);
	chatString=this->jsonParse.valueToString(chat);
	LOG(DEBUG)<<chatString;
	DBtuple putChat("chat_"+conversationId,chatString);
	DB->put(putChat);
	return lastsMessagesString;
}

msg_t HandlerChat::handleGetChat(struct http_message *hm){
	/**Maneja el get de un chat particular.**/
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
			msg.body=this->readChat(getChat.value,user,message_id,conversation_id);
		}
	}else{
		LOG(INFO) << "Esta conversacion no le pertenece";
		msg.status=StatusCode::UNAUTHORIZED;
	}

	return msg;
}

msg_t HandlerChat::handleGet(struct http_message *hm) {
	/**	Recibo el get de un mensaje y devuelvo un accepted si se realizo correctamente**/
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

