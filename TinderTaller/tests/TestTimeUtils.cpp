#include "../include/gtest/gtest.h"
#include "../include/TimeUtils.h"
#include <iostream>
#include <string>
#include <iostream>

using namespace std;
TEST(TimeUtils,stringToTimeDifferencefromNow){
	TimeUtils timeUtils;
	string strTime=timeUtils.timeToString();
	sleep(1);
	double difTime=timeUtils.stringtoTimeDifferencefromNow(strTime);
	//cout <<difTime<<"\n";
	EXPECT_GE(difTime,1);
}
