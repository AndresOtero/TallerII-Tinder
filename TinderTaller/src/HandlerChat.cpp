/*
 * HandlerChat.cpp
 *
 *  Created on: 21 de abr. de 2016
 *      Author: andres
 */

#include "HandlerChat.h"

HandlerChat::~HandlerChat() {
	// TODO Auto-generated destructor stub
}
HandlerChat::HandlerMatch(shared_ptr<DataBase> DB) {
	/**Creo el handler de match**/
	this->DB=DB;
}
bool HandlerChat::isHandler(struct http_message *hm) {
	/**Creo el handler de users**/
	return (httpReqParser.prefixType(hm)==CHAT);
}
msg_t HandlerChat::handle(struct http_message *hm) {

}
