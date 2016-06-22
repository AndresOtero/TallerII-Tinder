/*
 * Interest.h
 *
 *  Created on: May 25, 2016
 *      Author: ediaz
 */

#ifndef ENTITIES_INTEREST_H_
#define ENTITIES_INTEREST_H_
#include <string>
#include "json/json.h"

using namespace std;

class Interest {
private:
	string category;
	string value;
public:
	Interest();
	void changeInterest(string category,string value);
	Json::Value getJsonValue();
	virtual ~Interest();
	string getCategory();
	void setCategory(string category);
	string getValue();
	void setValue(string value);
};

#endif /* ENTITIES_INTEREST_H_ */
