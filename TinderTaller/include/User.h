/*
 * User.h
 *
 *  Created on: May 24, 2016
 *      Author: ediaz
 */

#ifndef ENTITIES_USER_H_
#define ENTITIES_USER_H_

#include <string>
#include <vector>
using namespace std;

class User {
private:
	string id;
	string idShared;
	string email;
	string password;
	string gcmRegistrationId;
	int quantitySearchDaily;
	string dateLastUpdateSearch;
	vector<string> idUserMatchs;
	double latitude;
	double longitude;

public:
	User();
	virtual ~User();
	string getId();
	void setId(string id);
	string getIdShared();
	void setIdShared(string idShared);
	string getEmail();
	void setEmail(string email);
	string getPassword();
	void setPassword(string password);
	string getGcmRegistrationId();
	void setGcmRegistrationId(string gcmRegistrationId);
	int getQuantitySearchDaily();
	void setQuantitySearchDaily(int quantitySearchDaily);
	string getDateLastUpdateSearch();
	void setDateLastUpdateSearch(string dateLastUpdateSearch);
	vector<string> getIdUserMatchs();
	void setIdUserMatchs(vector<string> idUserMatchs);
	double getLatitude();
	void setLatitude(double latitude);
	double getLongitude();
	void setLongitude(double longitude);
};

#endif /* ENTITIES_USER_H_ */
