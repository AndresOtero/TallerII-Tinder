/*
 * UserDao.cpp
 *
 *  Created on: May 24, 2016
 *      Author: ediaz
 */

#include "UserDao.h"

UserDao::UserDao(shared_ptr<DataBase> dataBase) {
	this->dataBase = dataBase;
}

UserDao::~UserDao() {
}

User UserDao::getUser(string idUser){
	//Id en el Shared
	DBtuple key(idUser + "_id");
	this->dataBase->get(key);

	string userInJsonShared = sharedClient.getUser(key.value).body;//TODO FALTA CONTROLAR EL STATUS DEL REQUEST
	Json::Value responseJson = jsonParser.stringToValue(userInJsonShared);
	string user = jsonParser.valueToString(responseJson["user"]);

	return buildUser(idUser, user);
}

User UserDao::buildUser(string idUser, string userInJsonShared){
	User user;
	user.setId(idUser);
	user.setEmail(idUser);

	//Gcm para el android
	DBtuple keyGcm(idUser + "_gcmId");
	this->dataBase->get(keyGcm);
	user.setGcmRegistrationId(keyGcm.value);

	//Password en el Shared
	DBtuple keyPass(idUser + "_pass");
	this->dataBase->get(keyPass);
	user.setPassword(keyPass.value);

	//QuantitySearchDaily - Cantidad de busquedas diarias
	DBtuple keyQuantitySearchDaily(idUser + "_quantitySearchDaily");
	this->dataBase->get(keyQuantitySearchDaily);
	int quantity = 0;
	if (!keyQuantitySearchDaily.value.empty()){
		quantity = atoi(keyQuantitySearchDaily.value.c_str());
	}
	user.setQuantitySearchDaily(quantity);

	//DateLastUpdateSearch - Fecha de la ultima busqueda realizada
	user.setDateLastUpdateSearch("");
	DBtuple keyDateLastUpdateSearch(idUser + "_dateLastUpdateSearch");
	this->dataBase->get(keyDateLastUpdateSearch);

	if (!keyDateLastUpdateSearch.value.empty()){
		//Verifico si tengo que actualizar la cantidad de busquedas de candidatos diarias.
		double dif = timeUtils.stringtoTimeDifferencefromNow(user.getDateLastUpdateSearch());
		//TODO PREGUNTARLE A ANDY SI VIENE EN HORAS, MIN O SEGUNDOS O LO Q SEA
		if (dif > DIFERENCE_TIME){
			user.setQuantitySearchDaily(0);
			keyQuantitySearchDaily.value = "0";
			this->dataBase->put(keyQuantitySearchDaily);

			user.setDateLastUpdateSearch("");
			keyDateLastUpdateSearch.value = user.getDateLastUpdateSearch();
			this->dataBase->put(keyDateLastUpdateSearch);
		} else {
			//Cargo lo que haya
			user.setDateLastUpdateSearch(keyDateLastUpdateSearch.value);
		}
	}

	//IdUserMatchs - Ids de los usuarios con los cuales hubo match
	DBtuple keyIdUserMatchs(idUser + "_idUserMatchs");
	this->dataBase->get(keyIdUserMatchs);
	Json::Value idsJson = jsonParser.stringToValue(keyIdUserMatchs.value);
	vector<string> idUserMatchs = jsonParser.getVectorFromValue(idsJson["idUserMatchs"]);
	user.setIdUserMatchs(idUserMatchs);

	//IdUserMatchs - Ids de los usuarios con los cuales se espera tener match (candidatos seleccionados)
	DBtuple keyIdUserCandidatesMatchs(idUser + "_idUserCandidatesMatchs");
	this->dataBase->get(keyIdUserCandidatesMatchs);
	Json::Value idsCandidatesJson = jsonParser.stringToValue(keyIdUserCandidatesMatchs.value);
	vector<string> idUserCandidatesMatchs = jsonParser.getVectorFromValue(idsCandidatesJson["idUserCandidatesMatchs"]);
	user.setIdUserCandidatesMatchs(idUserCandidatesMatchs);

	//Obtengo el usuario del Shared
	Json::Value responseJson = jsonParser.stringToValue(userInJsonShared);
	user.setIdShared(jsonParser.getStringFromValue(responseJson, "id"));
	user.setName(jsonParser.getStringFromValue(responseJson, "name"));
	user.setAlias(jsonParser.getStringFromValue(responseJson, "alias"));
	user.setSex(jsonParser.getStringFromValue(responseJson, "sex"));
	user.setUrlPhotoProfile(jsonParser.getStringFromValue(responseJson, "photo_profile"));
	int age = atoi(jsonParser.getStringFromValue(responseJson, "age").c_str());
	user.setBirthday(age);

	Json::Value interestsJson = responseJson["interests"];
	vector<Interest> interests = jsonParser.getInterest(interestsJson);
	user.setInterests(interests);
	string latitude = jsonParser.getStringFromValue(responseJson["location"], "latitude");
	user.setLatitude(atof(latitude.c_str()));
	string longitude = jsonParser.getStringFromValue(responseJson["location"], "longitude");
	user.setLongitude(atof(longitude.c_str()));

	return user;
}

vector<User> UserDao::getUsers(){
	vector<User> users;
	string responseInJsonShared = sharedClient.getUsers().body;//TODO FALTA CONTROLAR EL STATUS DEL REQUEST
	Json::Value usersInJsonShared = jsonParser.stringToValue(responseInJsonShared);

	vector<string> usersJson = jsonParser.getVectorFromValue(usersInJsonShared["users"]);

	for( string userJson : usersJson ){
		Json::Value valueUser = jsonParser.stringToValue(userJson);
		string idEmail = jsonParser.getStringFromValue(valueUser, "email");
		User user = buildUser(idEmail, userJson);

		users.push_back(user);
	}

	return users;
}

User UserDao::increaseQuantitySearchDaily(User user){
	int quantitySearchDaily = user.getQuantitySearchDaily();
	quantitySearchDaily++;
	user.setQuantitySearchDaily(quantitySearchDaily);
	user.setDateLastUpdateSearch(timeUtils.timeToString());

	stringstream numeroCadena;
	numeroCadena << user.getQuantitySearchDaily();
	DBtuple keyQuantitySearchDaily(user.getId() + "_quantitySearchDaily", numeroCadena.str());
	this->dataBase->put(keyQuantitySearchDaily);

	DBtuple keyDateLastUpdateSearch(user.getId() + "_dateLastUpdateSearch", user.getDateLastUpdateSearch());
	this->dataBase->put(keyDateLastUpdateSearch);

	return user;
}

string UserDao::cleanString(string idUserCandidateMatch){
	/*
	 * Ejemplo de como viene:
	 * Name : idUserCandidateMatch
	 * Details:"\"RobertoM50.758326710562@gmail.com\"\n"
	 *
	 * Deberia de quedar:
	 * Details:"RobertoM50.758326710562@gmail.com"
	 */

	int length = idUserCandidateMatch.size() - 3;
	string idOk = idUserCandidateMatch.substr(1, length);

	return idOk;
}

bool UserDao::putMatch(User user, User userToMatch){
	//Actualizo los matchs del usuario que invoco la peticion
	Json::Value root;
	Json::Value data;
	vector<string> idUserMatchs = user.getIdUserMatchs();
	idUserMatchs.push_back(userToMatch.getId());
	for(string id : idUserMatchs){
		data.append(id);
	}
	root["idUserMatchs"] = data;
	DBtuple keyIdUserMatchs(user.getId() + "_idUserMatchs");
	keyIdUserMatchs.value = jsonParser.valueToString(root);
	bool userMatchOk = this->dataBase->put(keyIdUserMatchs);

	//Actualizo los matchs del candidato
	Json::Value rootCandidate;
	Json::Value dataCandidate;
	vector<string> idUserToMatchs = userToMatch.getIdUserMatchs();
	idUserToMatchs.push_back(user.getId());
	for(string id : idUserToMatchs){
		dataCandidate.append(id);
	}

	rootCandidate["idUserMatchs"] = dataCandidate;
	DBtuple keyIdUserToMatchs(userToMatch.getId() + "_idUserMatchs");
	keyIdUserToMatchs.value = jsonParser.valueToString(rootCandidate);
	bool userToMatchOk = this->dataBase->put(keyIdUserToMatchs);

	//Saco el usuario desde el candidato
	Json::Value rootUserCandidate;
	Json::Value dataUserCandidate;
	for(string id : userToMatch.getIdUserCandidatesMatchs()){
		id = cleanString(id);
		if(user.getId().compare(id.c_str()) != 0){
			dataUserCandidate.append(id);
		}
	}
	rootUserCandidate["idUserCandidatesMatchs"] = dataUserCandidate;
	DBtuple keyIdUserCandidateMatchs(userToMatch.getId() + "_idUserCandidatesMatchs");
	keyIdUserCandidateMatchs.value = jsonParser.valueToString(rootUserCandidate);
	bool userToMatchCandidateOk = this->dataBase->put(keyIdUserCandidateMatchs);

	if(userMatchOk && userToMatchOk && userToMatchCandidateOk){
		return true;
	}

	return false;
}

bool UserDao::putCandidateMatch(User user, User userToMatch){
	//Actualizo los candidatos a matchs del usuario que invoco la peticion
	Json::Value root;
	Json::Value data;
	vector<string> idUserCandidatesMatchs = user.getIdUserCandidatesMatchs();
	idUserCandidatesMatchs.push_back(userToMatch.getId());
	for(string id : idUserCandidatesMatchs){
		data.append(id);
	}
	root["idUserCandidatesMatchs"] = data;
	DBtuple keyIdUserCandidatesMatchs(user.getId() + "_idUserCandidatesMatchs");
	keyIdUserCandidatesMatchs.value = jsonParser.valueToString(root);

	return this->dataBase->put(keyIdUserCandidatesMatchs);
}

vector<User> UserDao::getCandidatesForIdUser(string idUser){
	vector<User> users = getUsers();
	if (idUser.empty()){
		return users;
	}

	vector<User> usersOk;

	for (User user : users){
		if (idUser.compare(user.getId().c_str()) != 0){
			usersOk.push_back(user);
		}
	}

	return usersOk;
}
