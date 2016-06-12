/*
 * TokenAuthentificatorMock.h
 *
 *  Created on: Jun 11, 2016
 *      Author: andres
 */
#include "../include/TokenAuthentificatorInterface.h"
#ifndef TOKENAUTHENTIFICATORMOCK_H_
#define TOKENAUTHENTIFICATORMOCK_H_

class TokenAuthentificatorMock: public TokenAuthentificatorInterface {
public:
	TokenAuthentificatorMock();
	std::string createJsonToken(std::string user,std::string time);
	std::string createJsonToken(std::string user) ;
	string getUserName(string jsonToken) ;
	bool deleteJsonTokenUser(string jsonToken) ;
	bool validateJsonToken(std::string token) ;
	virtual ~TokenAuthentificatorMock();
};

#endif /* TOKENAUTHENTIFICATORMOCK_H_ */
