/*
 * Configuration.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: andres
 */

#include "Configuration.h"
#include <string>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>
shared_ptr<Configuration> Configuration::configurationInstance = NULL; //Singleton Patron
bool Configuration::set = false; //Singleton Patron
string Configuration::pathJson="";
shared_ptr<Configuration> Configuration::getConfiguration(){
	/**Singleton consigue la unica instancia del objeto**/
	if(!configurationInstance){
		shared_ptr<Configuration> servInst(new Configuration(Configuration::pathJson.c_str()));
		Configuration::configurationInstance = servInst;
	}
	return configurationInstance;
}
void Configuration::setPath(string path){
	/**Setea el path al archivo de configuracion**/
	pathJson=path;
}
Configuration::Configuration(const char* pathJson) {
	/**Constructor de la configuracion**/
	LOG(INFO)<<"Creo nueva configuracion con path:"<<pathJson;
	std::ifstream configurationFile(pathJson, std::ifstream::binary);
	if(!configurationFile.good()){
		this->set=false;
		return;
	}
	this->set=true;
	string fileString;
	string lineString;
	while (std::getline(configurationFile, lineString)) {
		fileString += lineString;
	}
	this->jsonFile = jsonParser.stringToValue(fileString);

}
string Configuration::getStringAttribute(string attribute ){
	/**Busco un atributo de la configuracion y lo devuelvo como un string**/
	if(!set)return "";
	Json::Value val=this->jsonFile;
	return val[attribute].asString();
}
bool Configuration::getBooleanAttribute(string attribute ){
	/**Busco un atributo de la configuracion y lo devuelvo como un booleano**/
	if(!set)return false;
	Json::Value val=this->jsonFile;
	return (val[attribute].asString()=="true");
}

Configuration::~Configuration() {
	// TODO Auto-generated destructor stub
}

