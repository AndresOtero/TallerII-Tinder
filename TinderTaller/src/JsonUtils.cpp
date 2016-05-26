/*
 * JsonUtils.cpp
 *
 *  Created on: May 25, 2016
 *      Author: ediaz
 */

#include "JsonUtils.h"

JsonUtils::JsonUtils() {
	// TODO Auto-generated constructor stub

}

JsonUtils::~JsonUtils() {
	// TODO Auto-generated destructor stub
}

vector<Interest> JsonUtils::getInterestsJsonToObject(string userJson){
	Json::Value userValue = jsonParser.stringToValue(userJson);

	vector<Interest> interests;

	for (const Json::Value & interestValue : userValue["interests"]){
		Interest interest;

		interest.setCategory(jsonParser.getStringFromValue(interestValue, "category"));
		interest.setValue(jsonParser.getStringFromValue(interestValue, "value"));

		interests.push_back(interest);
	}

	return interests;
}

User JsonUtils::getUserJsonToObject(string idUser, string userJson){
	// TODO HAY Q VER COMO SE GUARDA EN LA BASE
	/*string id;
		string idShared;
		string email;
		string password;
		string gcmRegistrationId;
		int quantitySearchDaily;
		string dateLastUpdateSearch;
		int quantityMatchs;
		vector<string> idUserMatchs;
		double latitude;
		double longitude;*/

		//DBtuple userPass(mail+"_pass",pass);

	Json::Value userValue = jsonParser.stringToValue(userJson);

	User user;
	user.setId(idUser);
	user.setIdShared(jsonParser.getStringFromValue(userValue, "idShared"));
	user.setEmail(jsonParser.getStringFromValue(userValue, "email"));
	user.setPassword(jsonParser.getStringFromValue(userValue, "password"));
	user.setGcmRegistrationId(jsonParser.getStringFromValue(userValue, "gcmRegistrationId"));
	user.setQuantitySearchDaily(jsonParser.getIntFromValue(userValue, "quantitySearchDaily"));

	return user;
}

vector<User> JsonUtils::getUsersJsonToObject(string usersJson){
	//TODO FALTA HACERLO
	vector<User> u;
	return u;
}

string JsonUtils::getUserObjectToJson(User user){
	//TODO FALTA HACERLO
	string u;
	return u;
}
