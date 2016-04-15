/*
 * DataBase.cpp
 *
 *  Created on: 1 de abr. de 2016
 *      Author: andres
 */

#include "../include/DataBase.h"
#include <iostream>

using namespace rocksdb;

DataBase::DataBase(const std::string& dbPath, bool createIfMissing,
		bool eraseAll) {
	//DB creation
	//For more info on the DB. Go to: https://github.com/facebook/rocksdb/wiki/Basic-Operations
	// Optimize RocksDB. This is the easiest way to get RocksDB to perform well
	options.IncreaseParallelism();
	options.OptimizeLevelStyleCompaction();
	// create the DB if it's not already present
	if (dbPath.compare("") == 0) {
		LOG(FATAL)<< "El path esta vacio";
		return;
	}

	Options options;
	options.create_if_missing = createIfMissing;
	st = DB::Open(options, dbPath, &db);
	if (st.ok() && eraseAll) {
		this->deleteAll();
	}
	LOG(INFO)<< "Creo base de datos";
}

DataBase::~DataBase() {
	// TODO Auto-generated destructor stub
	LOG(INFO)<< "Borro la base de datos";
	delete db;
}

bool DataBase::ok() {
	return this->st.ok();
}
;

bool DataBase::put(DBtuple& tuple) {
	st = db->Put(WriteOptions(), tuple.key, tuple.value);
	return ok();
}
bool DataBase::get(DBtuple& tuple) {
	st = db->Get(ReadOptions(), tuple.key, &tuple.value);
	return ok();
}

string DataBase::status() {
	return st.ToString();
}
void DataBase::logStatus() {
	if (this->ok()) {
		LOG(INFO)<< status();
		return;
	}
	LOG(FATAL)<<status();
}
bool DataBase::delete_(DBtuple& tuple) {
	st = db->Delete(WriteOptions(), tuple.key);
	return ok();
}
bool DataBase::deleteAll() {
	DBtuple tuple;
	rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		tuple.key = it->key().ToString();
		this->delete_(tuple);
	}
	st = it->status();
	delete it;
	return ok();
}
