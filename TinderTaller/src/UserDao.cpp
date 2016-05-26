/*
 * UserDao.cpp
 *
 *  Created on: May 24, 2016
 *      Author: ediaz
 */

#include "UserDao.h"

UserDao::UserDao() {
	// TODO Auto-generated constructor stub
	//this->dataBase(new DataBase("./DBServer/", true, false));
	this->dataBase = new DataBase("./DBServer/", true, false);
}

UserDao::~UserDao() {
	// TODO Auto-generated destructor stub

	delete this->dataBase;
}

User getUserMock(){
	//TODO ESTO BORRARLO CUANDO ESTE TODO OK
	User user;
	user.setId("email1@gmail.com_1");
	user.setIdShared("1");
	user.setEmail("email1@gmail.com");
	user.setPassword("1234");
	user.setGcmRegistrationId("1asadsdasdasd");
	user.setQuantitySearchDaily(1);
	user.setDateLastUpdateSearch("20160502");

	vector<string> idUserMatchs;
	idUserMatchs.push_back("email2@gmail.com_2");
	idUserMatchs.push_back("email3@gmail.com_3");
	idUserMatchs.push_back("email4@gmail.com_4");
	idUserMatchs.push_back("email5@gmail.com_5");

	user.setIdUserMatchs(idUserMatchs);
	user.setLatitude(1);
	user.setLongitude(3);

	return user;
}

User UserDao::getUser(string idUser){
	// TODO MOCK - BORRARLO desde aca!
	if (true){
		return getUserMock();
	}
	// TODO MOCK - BORRARLO hasta aca!

	DBtuple key(idUser);
	this->dataBase->get(key);

	User user = jsonUtils.getUserJsonToObject(idUser, key.value);

	if (!user.getDateLastUpdateSearch().empty()){
		//Verifico si tengo que actualizar la cantidad de busquedas de candidatos diarias.
		double dif = timeUtils.stringtoTimeDifferencefromNow(user.getDateLastUpdateSearch());
		//TODO PREGUNTARLE A ANDY SI VIENE EN HORAS, MIN O SEGUNDOS O LO Q SEA
		if (dif > DIFERENCE_TIME){
			user.setQuantitySearchDaily(0);
			user.setDateLastUpdateSearch("");

			key.value = jsonUtils.getUserObjectToJson(user);
			this->dataBase->put(key);
		}
	}

	return user;
}

vector<User> getUsersMock(){
	//TODO ESTO BORRARLO CUANDO ESTE TODO OK
	vector<User> users;
	User user2;
	user2.setId("email2@gmail.com_2");
	user2.setIdShared("2");
	user2.setEmail("email2@gmail.com");
	user2.setPassword("1234");
	user2.setGcmRegistrationId("2asadsdasdasd");
	user2.setQuantitySearchDaily(2);
	user2.setDateLastUpdateSearch("20160502");

	vector<string> idUserMatchs;
	user2.setIdUserMatchs(idUserMatchs);

	user2.setLatitude(20);
	user2.setLongitude(3);

	users.push_back(user2);

	User user3;
	user3.setId("email3@gmail.com_3");
	user3.setIdShared("3");
	user3.setEmail("email3@gmail.com");
	user3.setPassword("1234");
	user3.setGcmRegistrationId("3asadsdasdasd");
	user3.setQuantitySearchDaily(10);
	user3.setDateLastUpdateSearch("20160502");

	vector<string> idUserMatchs3;
	idUserMatchs3.push_back("email1@gmail.com_1");
	idUserMatchs3.push_back("email4@gmail.com_4");
	idUserMatchs3.push_back("email5@gmail.com_5");
	user3.setIdUserMatchs(idUserMatchs3);

	user3.setLatitude(5);
	user3.setLongitude(6);

	users.push_back(user3);

	return users;
}


vector<User> UserDao::getUsers(){
	// TODO MOCK - BORRARLO desde aca!
	if (true){
		return getUsersMock();
	}
	// TODO MOCK - BORRARLO hasta aca!


	DBtuple key("users");
	this->dataBase->get(key);

	//TODO VER SI TENGO Q ACTUALIZAR LA CANTIDAD DE BUSQUEDAS DIARIAS TB O NO. CREO Q NO HACE FALTA

	return jsonUtils.getUsersJsonToObject(key.value);
}

User UserDao::increaseQuantitySearchDaily(User user){
	int quantitySearchDaily = user.getQuantitySearchDaily();
	quantitySearchDaily++;
	user.setQuantitySearchDaily(quantitySearchDaily);
	user.setDateLastUpdateSearch(timeUtils.timeToString());

	// TODO MOCK - BORRARLO desde aca!
	if (true){
		return user;
	}
	// TODO MOCK - BORRARLO hasta aca!

	string userJson = jsonUtils.getUserObjectToJson(user);
	DBtuple key(user.getId(), userJson);
	this->dataBase->put(key);

	return user;
}

User UserDao::increaseQuantityMatchs(User user, string idUserMatch){
	vector<string> matchs = user.getIdUserMatchs();
	matchs.push_back(idUserMatch);
	user.setIdUserMatchs(matchs);

	// TODO MOCK - BORRARLO desde aca!
	if (true){
		return user;
	}
	// TODO MOCK - BORRARLO hasta aca!

	string userJson = jsonUtils.getUserObjectToJson(user);
	DBtuple key(user.getId(), userJson);
	this->dataBase->put(key);

	return user;
}
