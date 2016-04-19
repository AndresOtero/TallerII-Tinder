/*
 * TestHTTPRequestParser.cpp
 *
 *  Created on: 18 de abr. de 2016
 *      Author: andres
 */
#include "../include/gtest/gtest.h"
#include "../include/HTTPRequestParser.h"
#include "../include/mongoose.h"
#include <vector>
#include <iostream>



TEST(HTTPRequestParser,parseUriToVector){
	HTTPRequestParser httpParser;
	http_message* hm=new http_message;
	hm->uri.p="users/id";
	vector<string> vS=httpParser.parsePrefix(hm);
	EXPECT_TRUE(vS[0]=="users");
	EXPECT_TRUE(vS[1]=="id");
	delete hm;
}
