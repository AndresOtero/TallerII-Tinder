/*
 * DataBase.cpp
 *
 *  Created on: 1 de abr. de 2016
 *      Author: andres
 */

#include "../include/DataBase.h"
#include <iostream>

using namespace rocksdb;
std::string kDBPath = "/tmp/rocksdb_simple_example";




DataBase::DataBase() {

	// Optimize RocksDB. This is the easiest way to get RocksDB to perform well
	options.IncreaseParallelism();
	options.OptimizeLevelStyleCompaction();
	// create the DB if it's not already present
	options.create_if_missing = true;
	Status s = DB::Open(options, kDBPath, &db);
	LOG(INFO)<< "Creo base de datos";
	this->st=s;
	//chequear s
	/*// open DB


	// Put key-value
	s = db->Put(WriteOptions(), "key1", Slice("value"));
	assert(s.ok());
	std::string value;
	// get value
	s = db->Get(ReadOptions(), "key1", &value);
	assert(s.ok());
	assert(value == "value");

	// atomically apply a set of updates
	{
		WriteBatch batch;
		batch.Delete("key1");
		batch.Put("key2", value);
		s = db->Write(WriteOptions(), &batch);
	}

	s = db->Get(ReadOptions(), "key1", &value);
	assert(s.IsNotFound());

	db->Get(ReadOptions(), "key2", &value);
	assert(value == "value");*/
}

DataBase::~DataBase() {
	// TODO Auto-generated destructor stub
	/* BackupEngine* backup_engine;
	    Status s = BackupEngine::Open(Env::Default(), BackupableDBOptions("/tmp/rocksdb_backup"), &backup_engine);
	    assert(s.ok());
	    backup_engine->CreateNewBackup(db);*/
	LOG(INFO)<< "Borro la base de datos";
	delete db;
}
bool DataBase::ok(){

	return this->st.ok();
};

bool DataBase::put(string key , string value){
	Status s = db->Put(WriteOptions(), key, value);
	st=s;
	return ok();
}
bool DataBase::get(string key , string* value){
	Status s = db->Get(ReadOptions(), key, value);
	st=s;
	return ok();
}

string DataBase::status(){
	return st.ToString();
}
bool DataBase::delete_(string key){

	Status s = db->Delete(WriteOptions(), key);
	st=s;
	return ok();
}
