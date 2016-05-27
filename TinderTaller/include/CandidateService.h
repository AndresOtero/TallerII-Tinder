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
//#include <math.h>
#include <iostream>
//#include <algorithm>
#include "User.h"
#include "UserDao.h"
#include "SharedClient.h"
#include "JsonUtils.h"

#define MAX_SEARCH_CANDIDATE  10  //TODO esto hay que sacarlo a una properties
#define PERCENTAGE_LEAST_VOTED 1 //TODO esto hay que sacarlo a una properties
#define MAX_LATITUDE 100 //TODO esto hay que sacarlo a una properties
#define MAX_LONGITUDE 500  //TODO esto hay que sacarlo a una properties

using namespace std;

typedef enum StatusCodeSearch {
	OK_SEARCH = 200, ERROR_LIMIT_DAILY = 201
} StatusCodeSearch;

typedef struct search {
	StatusCodeSearch status;
	vector<User> candidates;

	search(StatusCodeSearch status, vector<User> candidates){
		change(status, candidates);
	}

	void change(StatusCodeSearch status, vector<User> candidates){
		this->status = status;
		this->candidates = candidates;
	}

	search(){};
} search_candidate_t;

class CandidateService {
private:
	UserDao userDao;
	SharedClient sharedClient;
	JsonUtils jsonUtils;
	vector<User> getUsersLeastVoted(vector<User> candidates);
	vector<User> getUsersNotMatch(User user, vector<User> candidates);
	vector<User> getUsersNear(User user, vector<User> candidates);
	vector<User> getUsersCommonInterests(User user, vector<User> candidates);
public:
	CandidateService();
	virtual ~CandidateService();
	search_candidate_t searchCandidate(string idUser);
};

#endif /* SERVICES_CANDIDATESERVICE_H_ */
