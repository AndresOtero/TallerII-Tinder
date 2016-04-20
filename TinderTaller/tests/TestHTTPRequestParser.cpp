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
TEST(HTTPRequestParser,getId){
	HTTPRequestParser httpParser;
	http_message* hm=new http_message;
	hm->uri.p="/users/1000/";
	EXPECT_TRUE(1000==httpParser.getId(hm));
	hm->uri.p="/users/mil/";
	EXPECT_TRUE(-1==httpParser.getId(hm));
	delete hm;
}

TEST(HTTPRequestParser,methodTypePut) {
	HTTPRequestParser httpParser;
	http_message* hm = new http_message;
	string put = "PUT";
	hm->method.p = put.c_str();
	hm->method.len = put.size();
	EXPECT_TRUE(httpParser.methodType(hm) == PUT);
	delete hm;
}
TEST(HTTPRequestParser,methodTypePost) {
	HTTPRequestParser httpParser;
	http_message* hm = new http_message;
	string post = "POST";
	hm->method.p = post.c_str();
	hm->method.len = post.size();
	EXPECT_TRUE(httpParser.methodType(hm) == POST);
	delete hm;
}
TEST(HTTPRequestParser,methodTypeGet) {
	HTTPRequestParser httpParser;
	http_message* hm = new http_message;
	string get = "GET";
	hm->method.p = get.c_str();
	hm->method.len = get.size();
	EXPECT_TRUE(httpParser.methodType(hm) == GET);
	delete hm;
}
TEST(HTTPRequestParser,methodTypeDelete) {
	HTTPRequestParser httpParser;
	http_message* hm = new http_message;
	string delete_ = "DELETE";
		hm->method.p = delete_.c_str();
		hm->method.len = delete_.size();
		EXPECT_TRUE(httpParser.methodType(hm) == DELETE);
	delete hm;
}
TEST(HTTPRequestParser,methodTypeInvalid) {
	HTTPRequestParser httpParser;
	http_message* hm = new http_message;
	string andy = "ANDY";
	hm->method.p = andy.c_str();
	hm->method.len = andy.size();
	EXPECT_TRUE(httpParser.methodType(hm) == INVALID_METHOD);
	delete hm;
}
