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

vector<string> User::getIdUserMatchs() const{
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

bool User::operator< (const User user) const {
	return (this->getIdUserMatchs().size() < user.getIdUserMatchs().size());
}

void User::setName(string name){
	this->name = name;
}

string User::getName(){
	return this->name;
}

void User::setAlias(string alias){
	this->alias = alias;
}

string User::getAlias(){
	return this->alias;
}

void User::setSex(string sex){
	this->sex = sex;
}

string User::getSex(){
	return this->sex;
}

void User::setBirthday(int birthday){
	this->birthday = birthday;
}

int User::getBirthday(){
	return this->birthday;
}

void User::setUrlPhotoProfile(string urlPhotoProfile){
	this->urlPhotoProfile = urlPhotoProfile;
}

string User::getUrlPhotoProfile(){
	return this->urlPhotoProfile;
}
vector<Interest> User::getPreferences() {
	return preferences;
}

void User::setPreferences(vector<Interest> preferences) {
	this->preferences = preferences;
}
void User::setInterests(vector<Interest> interests){
	this->interests = interests;
}

vector<Interest> User::getInterests(){
	return this->interests;
}

void User::setIdUserCandidatesMatchs(vector<string> idUserCandidatesMatchs){
	this->idUserCandidatesMatchs = idUserCandidatesMatchs;
}

vector<string> User::getIdUserCandidatesMatchs(){
	return this->idUserCandidatesMatchs;
}

void User::setPhotoProfile(string photoProfile){
	this->photoProfile = photoProfile;
}

string User::getPhotoProfile(){
	return this->photoProfile;
}
