/*
 * Test.cpp
 *
 *  Created on: 1 de abr. de 2016
 *      Author: andres
 */
#include "gtest/gtest.h"
#include "../include/DataBase.h"
#include <iostream>

TEST(DataBase,CreateADataBase){
	DataBase* db=new DataBase();
	EXPECT_TRUE(db->ok());
	delete db;
}
TEST(DataBase, StoreAValue)
{
	DataBase* db=new DataBase();
	EXPECT_TRUE(db->ok());
	EXPECT_TRUE(db->put("hola","mundo"));
	delete db;

}
TEST(DataBase, GetAValue)
{
	DataBase* db=new DataBase();
	EXPECT_TRUE(db->ok());
	EXPECT_TRUE(db->put("hola","mundo"));
	string mundo;
	EXPECT_TRUE(db->get("hola",&mundo));
	EXPECT_TRUE(mundo=="mundo");
	delete db;
}
TEST(DataBase, DeleteAKey)
{
	DataBase* db=new DataBase();
	EXPECT_TRUE(db->ok());
	EXPECT_TRUE(db->put("hola","mundo"));
	string mundo;
	EXPECT_TRUE(db->get("hola",&mundo));
	EXPECT_TRUE(db->delete_("hola"));
	EXPECT_FALSE(db->get("hola",&mundo));
	delete db;
}

int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();

}




