/*
 * TokenAuthentificatorMock.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: andres
 */

#include "TokenAuthentificatorMock.h"

TokenAuthentificatorMock::TokenAuthentificatorMock() {
	// TODO Auto-generated constructor stub
	this->idMail="andy@yahoo.com";
}
std::string TokenAuthentificatorMock::createJsonToken(std::string user,std::string time){
	return user;
}

std::string TokenAuthentificatorMock::createJsonToken(std::string user) {
	return user;
}
string TokenAuthentificatorMock::getUserName(string jsonToken) {
	return idMail;
}

bool TokenAuthentificatorMock::deleteJsonTokenUser(string jsonToken) {
	return true;
}


bool TokenAuthentificatorMock::validateJsonToken(std::string token) {
	return true;
}
void TokenAuthentificatorMock::match() {
	idMail="eli@yahoo.com";
}
TokenAuthentificatorMock::~TokenAuthentificatorMock() {
	// TODO Auto-generated destructor stub
}

