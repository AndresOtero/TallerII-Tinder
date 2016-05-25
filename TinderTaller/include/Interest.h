/*
 * Interest.h
 *
 *  Created on: May 25, 2016
 *      Author: ediaz
 */

#ifndef ENTITIES_INTEREST_H_
#define ENTITIES_INTEREST_H_

#include <string>

using namespace std;

class Interest {
private:
	string category;
	string value;
public:
	Interest();
	virtual ~Interest();
	string getCategory();
	void setCategory(string category);
	string getValue();
	void setValue(string value);
};

#endif /* ENTITIES_INTEREST_H_ */
