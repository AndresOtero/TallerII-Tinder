#include "../include/gtest/gtest.h"
#include "../include/User.h"

TEST(User,alias){
	User* user=new User();
	user->setAlias("Robertito");
	EXPECT_TRUE(user->getAlias()=="Robertito");
	delete user;
}
TEST(User,birthday){
	User* user=new User();
	user->setBirthday(24062016);
	EXPECT_TRUE(user->getBirthday()==24062016);
	delete user;
}
TEST(User,dateLastSearch){
	User* user=new User();
	user->setDateLastUpdateSearch("24/06/16-00:00:00");
	EXPECT_TRUE(user->getDateLastUpdateSearch()=="24/06/16-00:00:00");
	delete user;
}
TEST(User,mail){
	User* user=new User();
	user->setEmail("Andy@gmail.com");
	EXPECT_TRUE(user->getEmail()=="Andy@gmail.com");
	delete user;
}
TEST(User,gcm){
	User* user=new User();
	user->setGcmRegistrationId("GcmId");
	EXPECT_TRUE(user->getGcmRegistrationId()=="GcmId");
	delete user;
}
TEST(User,ID){
	User* user=new User();
	user->setId("Id");
	EXPECT_TRUE(user->getId()=="Id");
	delete user;
}
TEST(User,IdShared){
	User* user=new User();
	user->setIdShared("IdShared");
	EXPECT_TRUE(user->getIdShared()=="IdShared");
	delete user;
}
TEST(User,IdUserCandidatesMatchs){
	User* user=new User();
	vector<string> vec;
	vec.push_back("carlos");
	vec.push_back("juan");
	user->setIdUserCandidatesMatchs(vec);
	vector<string> vecTest=user->getIdUserCandidatesMatchs();
	string test;
	EXPECT_TRUE(vecTest[0]=="carlos");
	EXPECT_TRUE(vecTest[1]=="juan");
	delete user;
}
TEST(User,IdUserMatchs){
	User* user=new User();
	vector<string> vec;
	vec.push_back("carlos");
	vec.push_back("juan");
	user->setIdUserMatchs(vec);
	vector<string> vecTest=user->getIdUserMatchs();
	string test;
	EXPECT_TRUE(vecTest[0]=="carlos");
	EXPECT_TRUE(vecTest[1]=="juan");
	delete user;
}
TEST(User,Latitude){
	User* user=new User();
	user->setLatitude(12.05);
	EXPECT_TRUE(user->getLatitude()==12.05);
	delete user;
}
TEST(User,Longitude){
	User* user=new User();
	user->setLongitude(12.05);
	EXPECT_TRUE(user->getLongitude()==12.05);
	delete user;
}
TEST(User,name){
	User* user=new User();
	user->setName("Andy");
	EXPECT_TRUE(user->getName()=="Andy");
	delete user;
}
TEST(User,password){
	User* user=new User();
	user->setPassword("Andy");
	EXPECT_TRUE(user->getPassword()=="Andy");
	delete user;
}
TEST(User,quantity){
	User* user=new User();
	user->setQuantitySearchDaily(1);
	EXPECT_TRUE(user->getQuantitySearchDaily()==1);
	delete user;
}
TEST(User,sex){
	User* user=new User();
	user->setSex("M");
	EXPECT_TRUE(user->getSex()=="M");
	delete user;
}
TEST(User,photo){
	User* user=new User();
	user->setUrlPhotoProfile("M");
	EXPECT_TRUE(user->getUrlPhotoProfile()=="M");
	delete user;
}
TEST(User,interest){
	User* user=new User();
	Interest interest;
	interest.setCategory("Deporte");
	interest.setValue("Boca");
	vector<Interest> vecInt;
	vecInt.push_back(interest);
	user->setInterests(vecInt);
	vector<Interest> vecTest=user->getInterests();
	EXPECT_TRUE(vecTest[0].getCategory()=="Deporte");
	EXPECT_TRUE(vecTest[0].getValue()=="Boca");
	delete user;
}

/**

	user->setUrlPhotoProfile()
}**/
