/*
 * HTTPRequestParser.h
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */
#include <iostream>
#include "mongoose.h"
#include "HTTPRequest.h"
#include "easylogging++.h"
#include <vector>
#ifndef SRC_HTTPREQUESTPARSER_H_
#define SRC_HTTPREQUESTPARSER_H_
using namespace std;
class HTTPRequestParser {
public:
	HTTPRequestParser();
	MethodType methodType(struct http_message *hm);
	PrefixType prefixType(struct http_message *hm);
	vector<string> parsePrefix(struct http_message *hm);
	int getId(struct http_message *hm);
	virtual ~HTTPRequestParser();

private:
	vector<string> StringToVector(std::string const& str, char const delimiter);
	bool isPrefix(struct http_message *hm, string prefix, size_t position);
	bool isMethod(struct http_message *hm, string method);
};

#endif /* SRC_HTTPREQUESTPARSER_H_ */
