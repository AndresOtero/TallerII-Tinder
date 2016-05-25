/*
 * JsonUtils.h
 *
 *  Created on: May 25, 2016
 *      Author: ediaz
 */

/*#ifndef UTILS_JSONUTILS_H_
#define UTILS_JSONUTILS_H_*/

#ifndef SRC_JSONUTILS_H_
#define SRC_JSONUTILS_H_



#include <vector>
#include <string>
#include "JsonParser.h"
#include "Interest.h"
#include "User.h"

using namespace std;

class JsonUtils {
private:
	JsonParser jsonParser;
public:
	JsonUtils();
	virtual ~JsonUtils();
	vector<Interest> getInterestsJsonToObject(string userJson);
	User getUserJsonToObject(string idUser, string userJson);
	vector<User> getUsersJsonToObject(string usersJson);
	string getUserObjectToJson(User user);
};

#endif /* SRC_JSONUTILS_H_ */
