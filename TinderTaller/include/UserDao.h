/*
 * UserDao.h
 *
 *  Created on: May 24, 2016
 *      Author: ediaz
 */

#ifndef DAOS_USERDAO_H_
#define DAOS_USERDAO_H_

#include <string>
#include <vector>
#include "DataBase.h"
#include "TimeUtils.h"
#include "User.h"
#include "JsonParser.h"
#include "SharedClient.h"
#include "Interest.h"

#define DIFERENCE_TIME  24
using namespace std;

class UserDao {
private:
	//shared_ptr<DataBase> dataBase(new DataBase("./DBServer/", true, false));
	//shared_ptr<DataBase> dataBase;
	shared_ptr<DataBase> dataBase;
	TimeUtils timeUtils;
	JsonParser jsonParser;
	shared_ptr<SharedClient> sharedClient;
	User buildUser(string idUser, string userInJsonShared);
	string cleanString(string idUserCandidateMatch);
public:
	UserDao(shared_ptr<DataBase> dataBase,shared_ptr<SharedClient> sharedClient);
	virtual ~UserDao();
	User getUser(string idUser);
	vector<User> getUsers();
	User increaseQuantitySearchDaily(User user);
	vector<User> getCandidatesForIdUser(string idUser);
	bool putMatch(User user, User userToMatch);
	bool putCandidateMatch(User user, User userToMatch);
};

#endif /* DAOS_USERDAO_H_ */
