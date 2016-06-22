/*
 * TimeUtils.cpp
 *
 *  Created on: 24 de abr. de 2016
 *      Author: andres
 */



#include "TimeUtils.h"

TimeUtils::TimeUtils() {
	/**Creo time utils**/
}
string TimeUtils::timeToString(){
	/**Devuelvo el string formateado**/
	time_t now;
	struct tm * tm;
	char buffer[80];
	time (&now);
	tm = localtime(&now);
	strftime(buffer,80,"%d-%m-%Y %I:%M:%S",tm);
	return string(buffer);
}

string TimeUtils::unixTimeToString(){
	/**Devuelvo el string el tiempo de unix en segundos**/
	time_t now;
	time (&now);
	return to_string(now);
}
double TimeUtils::stringtoTimeDifferencefromNow(string stringTime){
	/**Devuelvo como double la diferencia de tiempo entre el string que me pasaron y ahora**/
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

