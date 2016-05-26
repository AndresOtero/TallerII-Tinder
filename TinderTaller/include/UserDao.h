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
#include "JsonUtils.h"
#include "TimeUtils.h"
#include "User.h"

#define DIFERENCE_TIME  24
using namespace std;

class UserDao {
private:
	//shared_ptr<DataBase> dataBase(new DataBase("./DBServer/", true, false));
	//shared_ptr<DataBase> dataBase;
	DataBase * dataBase;
	JsonUtils jsonUtils;
	TimeUtils timeUtils;
public:
	UserDao();
	virtual ~UserDao();
	User getUser(string idUser);
	vector<User> getUsers();
	User increaseQuantitySearchDaily(User user);
	User increaseQuantityMatchs(User user, string idUserMatch);
};

#endif /* DAOS_USERDAO_H_ */
