/*
 * TokenAuthentificator.h
 *
 *  Created on: 24 de abr. de 2016
 *      Author: andres
 */
#include <iostream>
#include <string>
#include <functional>
#include <ctime>
#include "../include/TimeUtils.h"

#ifndef SRC_TOKENAUTHENTIFICATOR_H_
#define SRC_TOKENAUTHENTIFICATOR_H_

class TokenAuthentificator {
private:
	TimeUtils timeUtils;
public:
	TokenAuthentificator();
	std::string createToken(std::string user);
	virtual ~TokenAuthentificator();
};

#endif /* SRC_TOKENAUTHENTIFICATOR_H_ */
