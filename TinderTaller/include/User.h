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
#include "Interest.h"
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
	string name;
	string alias;
	string sex;
	int birthday;
	string urlPhotoProfile;
	vector<Interest> interests;
	vector<string> idUserCandidatesMatchs;
	string photoProfile;
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
	vector<string> getIdUserMatchs() const;
	void setIdUserMatchs(vector<string> idUserMatchs);
	double getLatitude();
	void setLatitude(double latitude);
	double getLongitude();
	void setLongitude(double longitude);
	bool operator<(const User user) const;
	void setName(string name);
	string getName();
	void setAlias(string alias);
	string getAlias();
	void setSex(string sex);
	string getSex();
	void setBirthday(int birthday);
	int getBirthday();
	void setUrlPhotoProfile(string urlPhotoProfile);
	string getUrlPhotoProfile();
	void setInterests(vector<Interest> interests);
	vector<Interest> getInterests();
	void setIdUserCandidatesMatchs(vector<string> idUserCandidatesMatchs);
	vector<string> getIdUserCandidatesMatchs();
	void setPhotoProfile(string photoProfile);
	string getPhotoProfile();
};

#endif /* ENTITIES_USER_H_ */
