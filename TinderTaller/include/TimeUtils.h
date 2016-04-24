/*
 * TimeUtils.h
 *
 *  Created on: 24 de abr. de 2016
 *      Author: andres
 */
#include <iostream>
#include <string>
#include <functional>
#include <ctime>
#ifndef SRC_TIMEUTILS_H_
#define SRC_TIMEUTILS_H_
using namespace std;

class TimeUtils {
public:
	TimeUtils();
	string timeToString();
	double stringtoTimeDifferencefromNow(string stringTime);
	virtual ~TimeUtils();

};

#endif /* SRC_TIMEUTILS_H_ */
