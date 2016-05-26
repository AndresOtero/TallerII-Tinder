/*
 * HTTPRequestParser.cpp
 *
 *  Created on: 15 de abr. de 2016
 *      Author: andres
 */
#define FIRST_POSITION 1
#define SECOND_POSITION 2
#include "HTTPRequestParser.h"
#include <iostream>
using namespace std;

HTTPRequestParser::HTTPRequestParser() {
	/**Creo el htttp parser**/
	IdOk=true;
}

bool HTTPRequestParser::isPrefix(struct http_message *hm, string prefix,
		size_t position) {
	/**Compara un string con un prefijo con el prefijo del mensaje en la posicion position. Devuelve ture si es igual , false sino.**/
	std::vector < std::string > vec = parsePrefix(hm);
	return (vec[position] == prefix);
}

string HTTPRequestParser::getTokenFromHeader(struct http_message *hm){

	char token[200];
	struct mg_str *hdr = mg_get_http_header(hm, "Authorization");
	if(hdr==0){
		LOG(INFO)<<"HTTPParser: header incorrecto";
		return "";
	}
	string tokenUnparsed(hdr->p);
	size_t pos= tokenUnparsed.find_first_of("\r");
	string tokenParsed=tokenUnparsed.substr(0,pos);
	//for(int i=0;i<hdr->len;i++){
		//cout<<hdr->p[i];
	//}

	return tokenParsed;
}

vector<string> HTTPRequestParser::parsePrefix(struct http_message *hm) {
	/**Recibe el mensaje y devuelve el uri como un vector de strings**/
	vector < string > uri_parsed;
	string str { hm->uri.p };
	std::vector < std::string > uri_semi_parsed { StringToVector(str, '/') };
	for (std::vector<string>::iterator it = uri_semi_parsed.begin();
			it != uri_semi_parsed.end(); ++it) {
		string s = (*it);
		std::vector < std::string > b { StringToVector(s, ' ') };
		uri_parsed.insert(uri_parsed.end(), b.begin(), b.end());
	}
	return uri_semi_parsed;
}

bool HTTPRequestParser::isMethod(struct http_message *hm, string method) {
	/** Recibe un metodo en forma de string y un mensaje. Luego devuelve si el mensaje tiene es metodo es true , sino es false.**/
	string methodM = "";
	methodM.append(hm->method.p, hm->method.len);
	return (methodM.compare(method) == 0);
}

PrefixType HTTPRequestParser::prefixType(struct http_message *hm) {
	/**Recibe un mensaje y devuelve el tipo del primer elemento del uri**/
	if (isPrefix(hm, usersString, FIRST_POSITION)){
		return USERS;
	}
	if (isPrefix(hm, chatString, FIRST_POSITION)){
			return CHAT;
	}
	if (isPrefix(hm, matchString, FIRST_POSITION)){
			return MATCH;
		}
	if (isPrefix(hm, tokenString, FIRST_POSITION))
		return TOKEN;
	if (isPrefix(hm, interestsString, FIRST_POSITION))
			return INTERESTS;
	if (isPrefix(hm, singInString, FIRST_POSITION))
			return SINGIN;

}

bool isNumber(const std::string& s) {
	/* Devuelve true si es un numero, fasle si no lo es.***/
	return !s.empty()
			&& std::find_if(s.begin(), s.end(),
					[](char c) {return !std::isdigit(c);}) == s.end();
}

string HTTPRequestParser::getId(struct http_message *hm) {
	/**Recibe un mensaje y devuelve el segundo elemento del uri convertido a numero sino se puede devuelve -1.**/
	std::vector < std::string > vec = parsePrefix(hm);
	string id = vec[SECOND_POSITION];
	IdOk=true;
	return id;
}

bool HTTPRequestParser::idOk() {
	/**True si el id es correctamente parseado.**/
	return IdOk;
}

MethodType HTTPRequestParser::methodType(struct http_message *hm) {
	/**Recibe un mensaje y devuelve un el tipo de metodo que tiene ese mensaje.**/
	if (isMethod(hm, putString))
		return PUT;
	if (isMethod(hm, postString))
		return POST;
	if (isMethod(hm, getString))
		return GET;
	if (isMethod(hm, deleteString))
		return DELETE;

	return INVALID_METHOD;
}

HTTPRequestParser::~HTTPRequestParser() {
}

std::vector<std::string> HTTPRequestParser::StringToVector(
		std::string const& str, char const delimiter) {
	/**Convierte a un string en un vector de strings , spearandolos por el delimitador.**/
	std::vector < std::string > elems;
	std::stringstream ss(str);
	std::string item;
	while (std::getline(ss, item, delimiter)) {
		elems.push_back(item);
	}
	return elems;
}

