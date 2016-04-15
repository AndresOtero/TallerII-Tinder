/*
 * HTTPRequestParser.h
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */
#include <iostream>
#ifndef SRC_HTTPREQUESTPARSER_H_
#define SRC_HTTPREQUESTPARSER_H_

class HTTPRequestParser {
public:
	HTTPRequestParser();
    bool isUri(struct http_message *hm, std::string uri);
	virtual ~HTTPRequestParser();
};

#endif /* SRC_HTTPREQUESTPARSER_H_ */
