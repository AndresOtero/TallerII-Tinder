/*
 * HandlerToken.cpp
 *
 *  Created on: 1 de may. de 2016
 *      Author: andres
 */

#include "HandlerToken.h"

HandlerToken::HandlerToken(shared_ptr<DataBase> DB,shared_ptr<TokenAuthentificator> tokenAuthentificator,shared_ptr<SharedClient> sharedClient){
	/**Creo el handler de Token**/
	this->DB=DB;
	this->tokenAuthentificator=tokenAuthentificator;
	this->prefix=TOKEN;
	this->sharedClient= sharedClient;
}
msg_t HandlerToken::handleMsg(struct http_message *hm){
	if((httpReqParser.methodType(hm)!=POST)&&(!validateToken(hm))){
		return unathorized();
	}
	return handle(hm);
}

msg_t HandlerToken::handlePost(struct http_message *hm) {
	/**	Recibo el post de un mensaje y devuelvo un accepted si se realizo correctamente**/

	msg_t msg;
	Json::Value val = jsonParse.stringToValue(hm->body.p);
	string mail = jsonParse.getMail(hm->body.p);
	string pass = jsonParse.getPassword(hm->body.p);

	DBtuple tpPass(mail+"_pass");
	bool okPass=DB->get(tpPass);
	DBtuple tpId(mail+"_id");
	bool okId=DB->get(tpId);
	bool okDelete=this->deleteToken(hm);
	if (okPass&&(pass==tpPass.value)&&okDelete&&okId){
		string token=tokenAuthentificator->createJsonToken(mail);
		if(httpReqParser.parsePrefix(hm)[2]=="singin"){
			msg_t msgGet = sharedClient->getUser(tpId.value);
			val=jsonParse.stringToValue(msgGet.body);
			jsonParse.removeMember(val["user"],"id");
		}
		val["token"]=token;
		string  result = jsonParse.valueToString(val);
		LOG(INFO) << "Mando un mensaje";

		msg.change(CREATED, result);
	}else{
		msg=this->unathorized();
	}
	return msg;
}
msg_t HandlerToken::handleDelete(struct http_message *hm) {
	/**	Recibo el post de un mensaje y devuelvo un accepted si se realizo correctamente**/
	msg_t msg;
	if(this->deleteToken(hm)){
		msg.status=OK;
	}else{
		msg.status=BAD_REQUEST;
	}
	return msg;
}
HandlerToken::~HandlerToken() {
	// TODO Auto-generated destructor stub
}

