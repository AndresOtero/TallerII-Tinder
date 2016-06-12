#include "../include/gtest/gtest.h"
#include "../include/DataBase.h"
#include <iostream>

DBtuple tupleDB{
		"hola",
		"mundo"
	};
DBtuple tupleDB2{
		"chau",
		"mundo cruel"
	};
DBtuple tupleDBGet{
		"hola",
		""
	};
DBtuple tupleDBGet2{
		"chau",
		""
	};

TEST(DataBase,CreateADataBase){
	DataBase* db=new DataBase("./DBTest/",true,true);
	EXPECT_TRUE(db->ok());
	delete db;
}

TEST(DataBase, GetAValueWithoutErasing)
{
	DataBase* db=new DataBase("./DBTest/",true,false);
	EXPECT_TRUE(db->put(tupleDB));
	EXPECT_TRUE(db->ok());
	EXPECT_TRUE(db->get(tupleDBGet));
	EXPECT_TRUE(tupleDBGet.value=="mundo");
	delete db;
}
TEST(DataBase, StoreAValue)
{
	DataBase* db=new DataBase("./DBTest/",true,true);
	EXPECT_TRUE(db->ok());

	EXPECT_TRUE(db->put(tupleDB));
	delete db;

}
TEST(DataBase, NotGetAValueErasing)
{
	DataBase* db=new DataBase("./DBTest/",true,true);
	EXPECT_TRUE(db->ok());
	EXPECT_FALSE(db->get(tupleDBGet));
	delete db;
}
TEST(DataBase, GetAValueErasing)
{
	DataBase* db=new DataBase("./DBTest/",true,true);
	EXPECT_TRUE(db->ok());
	EXPECT_TRUE(db->put(tupleDB));
	EXPECT_TRUE(db->get(tupleDBGet));
	EXPECT_TRUE(tupleDBGet.value=="mundo");
	delete db;
}
TEST(DataBase, DeleteAKey)
{
	DataBase* db=new DataBase("./DBTest/",true,true);
	EXPECT_TRUE(db->ok());
	EXPECT_TRUE(db->put(tupleDB));
	EXPECT_TRUE(db->get(tupleDBGet));
	EXPECT_TRUE(db->delete_(tupleDB));
	EXPECT_FALSE(db->get(tupleDBGet));
	delete db;
}
TEST(DataBase, DeleteAllKeys)
{
	DataBase* db=new DataBase("./DBTest/",true,true);
	EXPECT_TRUE(db->ok());
	EXPECT_TRUE(db->put(tupleDB));
	EXPECT_TRUE(db->get(tupleDBGet));
	EXPECT_TRUE(db->put(tupleDB2));
	EXPECT_TRUE(db->get(tupleDBGet2));
	EXPECT_TRUE(db->deleteAll());
	EXPECT_FALSE(db->get(tupleDBGet));
	EXPECT_FALSE(db->get(tupleDBGet2));

	delete db;
}
TEST(DataBase, status)
{
	DataBase* db=new DataBase("./DBTest/",true,true);
	EXPECT_TRUE(db->ok());
	db->logStatus();
	delete db;
}
