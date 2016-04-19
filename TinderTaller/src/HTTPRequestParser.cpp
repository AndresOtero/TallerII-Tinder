/*
 * HTTPRequestParser.cpp
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */

#include "HTTPRequestParser.h"
using namespace std;
HTTPRequestParser::HTTPRequestParser() {

}
bool HTTPRequestParser::isPrefix(struct http_message *hm, string prefix,size_t position){
	std::vector<std::string> vec=parsePrefix(hm);
	return (vec[position]== prefix);
}
vector<string> HTTPRequestParser::parsePrefix(struct http_message *hm){
	vector<string> uri_parsed;
	string str{hm->uri.p};
    std::vector<std::string> uri_semi_parsed{StringToVector(str, '/')};
    for (std::vector<string>::iterator it = uri_semi_parsed.begin() ; it != uri_semi_parsed.end(); ++it){
    	std::vector<std::string> b{StringToVector(str, ' ')};
    	uri_parsed.insert(uri_parsed.end(), b.begin(), b.end());
    }
//**Hacer lista de  con los strings y parsear con ' '**//
	return uri_parsed;
}
bool HTTPRequestParser::isMethod(struct http_message *hm, string method){
	string methodM="";
	methodM.append(hm->method.p, hm->method.len);
	return (methodM.compare(method)==0);
}
PrefixType HTTPRequestParser::prefixType(struct http_message *hm){
	if(isPrefix(hm,usersString,0)) return USERS;
}

MethodType HTTPRequestParser::methodType(struct http_message *hm){
	if(isMethod(hm,putString)) return PUT;
	if(isMethod(hm,postString)) return POST;
	if(isMethod(hm,getString)) return GET;
	if(isMethod(hm,deleteString)) return DELETE;
	if(isMethod(hm,invalidMethodString)) return INVALID_METHOD;
}
HTTPRequestParser::~HTTPRequestParser() {
}
std::vector<std::string> HTTPRequestParser::StringToVector(std::string const& str, char const delimiter){

    std::vector<std::string> vec;
    std::string element;


    //we are going to loop through each character of the string slowly building an element string.
    //whenever we hit a delimiter, we will push the element into the vector, and clear it to get ready for the next element
    for_each(begin(str),end(str),[&](char const ch){
        if(ch!=delimiter){
            element+=ch;
        }
        else{
            if (element.length()>0){
            vec.push_back(element);
            element.clear();
            }
        }
    });


    //push in the last element if the string does not end with the delimiter
    if (element.length()>0){
        vec.push_back(element);
    }


    return vec;
}

