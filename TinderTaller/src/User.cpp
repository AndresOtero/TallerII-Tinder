/*
 * User.cpp
 *
 *  Created on: May 24, 2016
 *      Author: ediaz
 */

#include "User.h"

User::User() {
	// TODO Auto-generated constructor stub

}

User::~User() {
	// TODO Auto-generated destructor stub
}

string User::getId(){
	return this->id;
}

void User::setId(string id){
	this->id = id;
}

string User::getIdShared(){
	return this->idShared;
}

void User::setIdShared(string idShared){
	this->idShared = idShared;
}

string User::getEmail(){
	return this->email;
}

void User::setEmail(string email){
	this->email = email;
}

int User::getQuantitySearchDaily(){
	return this->quantitySearchDaily;
}

void User::setQuantitySearchDaily(int quantitySearchDaily){
	this->quantitySearchDaily = quantitySearchDaily;
}

string User::getDateLastUpdateSearch(){
	return this->dateLastUpdateSearch;
}

void User::setDateLastUpdateSearch(string dateLastUpdateSearch){
	this->dateLastUpdateSearch = dateLastUpdateSearch;
}

vector<string> User::getIdUserMatchs(){
	return this->idUserMatchs;
}

void User::setIdUserMatchs(vector<string> idUserMatchs){
	this->idUserMatchs = idUserMatchs;
}

double User::getLatitude(){
	return this->latitude;
}

void User::setLatitude(double latitude){
	this->latitude = latitude;
}

double User::getLongitude(){
	return this->longitude;
}

void User::setLongitude(double longitude){
	this->longitude = longitude;
}

string User::getPassword(){
	return this->password;
}

void User::setPassword(string password){
	this->password = password;
}

string User::getGcmRegistrationId(){
	return this->gcmRegistrationId;
}

void User::setGcmRegistrationId(string gcmRegistrationId){
	this->gcmRegistrationId = gcmRegistrationId;
}
