/*
 * CandidateService.h
 *
 *  Created on: May 24, 2016
 *      Author: ediaz
 */

#ifndef SERVICES_CANDIDATESERVICE_H_
#define SERVICES_CANDIDATESERVICE_H_

#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include <algorithm>
#include "User.h"
#include "UserDao.h"
#include "SharedClient.h"
#include "DataBase.h"
#include "easylogging++.h"

#define MAX_SEARCH_CANDIDATE  10  //TODO esto hay que sacarlo a una properties
#define PERCENTAGE_LEAST_VOTED 10 //TODO esto hay que sacarlo a una properties
#define MAX_LATITUDE 100 //TODO esto hay que sacarlo a una properties
#define MAX_LONGITUDE 500  //TODO esto hay que sacarlo a una properties

using namespace std;

typedef enum StatusCodeMatch {
	OK_SEARCH = 200, OK_UPDATE_MATCH = 201, ERROR_LIMIT_DAILY = 202
} StatusCodeMatch;

typedef struct search {
	StatusCodeMatch status;
	vector<User> candidates;

	search(StatusCodeMatch status, vector<User> candidates){
		change(status, candidates);
	}

	void change(StatusCodeMatch status, vector<User> candidates){
		this->status = status;
		this->candidates = candidates;
	}

	search(){};
} search_candidate_t;

class CandidateService {
private:
	shared_ptr<UserDao> userDao;
	SharedClient sharedClient;
	vector<User> getUsersLeastVoted(vector<User> candidates);
	vector<User> getUsersNotMatch(User user, vector<User> candidates);
	vector<User> getUsersNear(User user, vector<User> candidates);
	vector<User> getUsersCommonInterests(User user, vector<User> candidates);
public:
	CandidateService(shared_ptr<DataBase> DB);
	virtual ~CandidateService();
	search_candidate_t searchCandidate(string idUser);
	StatusCodeMatch match(string idUser, string idUserMatch);
};

#endif /* SERVICES_CANDIDATESERVICE_H_ */
