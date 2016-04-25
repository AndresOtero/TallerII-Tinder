/*
 * TimeUtils.cpp
 *
 *  Created on: 24 de abr. de 2016
 *      Author: andres
 */



#include "TimeUtils.h"

TimeUtils::TimeUtils() {
	// TODO Auto-generated constructor stub

}
string TimeUtils::timeToString(){
	time_t now;
	struct tm * tm;
	char buffer[80];
	time (&now);
	tm = localtime(&now);
	strftime(buffer,80,"%d-%m-%Y %I:%M:%S",tm);
	return string(buffer);
}


double TimeUtils::stringtoTimeDifferencefromNow(string stringTime){
	struct tm * tm=(struct tm *)new struct tm();
	struct tm *tmNow=(struct tm *)new  struct tm();
	strptime(stringTime.c_str(), "%d-%m-%Y %I:%M:%S", tm);
	string strNow=timeToString();
	strptime(strNow.c_str(), "%d-%m-%Y %I:%M:%S", tmNow);
	double dif= difftime(mktime(tmNow), mktime(tm));
	delete tm;
	delete tmNow;
	return dif;
}
TimeUtils::~TimeUtils() {
	// TODO Auto-generated destructor stub
}

