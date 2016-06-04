#include "../include/gtest/gtest.h"
#include "../include/Interest.h"


TEST(Interest,value) {
	Interest* interest=new Interest();
	interest->setValue("Boca");
	EXPECT_TRUE(interest->getValue()=="Boca");
	delete interest;
}
TEST(Interest,category) {
	Interest* interest=new Interest();
	interest->setCategory("Deporte");
	EXPECT_TRUE(interest->getCategory()=="Deporte");
	delete interest;
}
