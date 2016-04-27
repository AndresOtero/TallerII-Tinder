/*
 * HandlerInterface.cpp
 *
 *  Created on: 17 de abr. de 2016
 *      Author: andres
 */

#include "HandlerInterface.h"
/**
 HandlerInterface::HandlerInterface() {

 }
 **/
msg_t HandlerInterface::handleMsg(struct http_message *hm){
	if(!validateToken(hm)){
		return unathorized();
	}
	return handle(hm);
}
bool HandlerInterface::isHandler(struct http_message *hm) {
	/**Creo el handler de users**/
	return (httpReqParser.prefixType(hm)==prefix);
}

 bool HandlerInterface::validateToken(struct http_message *hm) {
/**	struct mg_str * mg_str = mg_get_http_header(hm, "Authorization");
	string jsonTokenUnparsed = string(mg_str->p);
	string jsonTokenHeader = string(hm->header_values[0].p);
	size_t tokenIn =jsonTokenHeader.find_first_of("Authorization: ");
	size_t tokenFin =jsonTokenHeader.find_first_of("///");

	cout<< "He aqui el token "<<jsonTokenUnparsed;
	//size_t tokenInPos = jsonTokenUnparsed.find_first_of("'token':u'");
	string divide(" . ");
	size_t tokenFinPos =jsonTokenUnparsed.find(divide);
	//string tokenTag("'token':u'");
	string tokenSubStr = jsonTokenUnparsed.substr(0,tokenFinPos-1);
	//Json::Value authJsonValue =jsonParse.stringToValue(authJsonStr);
	//string tokenStr= jsonParse.getStringFromValue(authJsonValue,"token");
	//LOG(INFO)<<tokenSubStr;
	**/
	/**	string jsonTokenHeader = string(hm->header_values[0].p);
	  for (int i = 0; i < MG_MAX_HTTP_HEADERS && hm->header_names[i].len > 0; i++) {
	    struct mg_str hn = hm->header_names[i];
	    struct mg_str hv = hm->header_values[i];
	    if (mg_vcasecmp(&hn, "Authorization")){
	    	cout<<"aleluya\n";
	    	cout<<"name: "<<hn.p<<"\n";
	    	cout<<"value: "<<hv.p<<"\n";
	    }
	  }***/
	 //return tokenAuthentificator->validateJsonToken(jsonTokenHeader);
	 return true;
}
 msg_t HandlerInterface::unathorized() {
	 msg_t msg;
	 string * result = new string();
	 result->append(json_example);
	 msg.change(UNAUTHORIZED, result);
	 return msg;
}
HandlerInterface::~HandlerInterface() {
}
