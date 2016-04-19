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
		bool deleteAll) {
	/**Creacion de la DB. Fuente: https://github.com/facebook/rocksdb/wiki/Basic-Operations
	 *
	 * **/
	// Optimize RocksDB. This is the easiest way to get RocksDB to perform well
	options.IncreaseParallelism();
	options.OptimizeLevelStyleCompaction();
	// create the DB if it's not already present
	if (dbPath.compare("") == 0) {
		LOG(FATAL)<< "El path esta vacio del base de datos";
		return;
	}

	Options options;
	options.create_if_missing = createIfMissing;
	st = DB::Open(options, dbPath, &db);
	if (st.ok() && deleteAll) {
		this->deleteAll();
	}
	LOG(INFO)<< "Creo base de datos";
}

DataBase::~DataBase() {
	/**Borro la base de datos**/
	LOG(INFO)<< "Borro la base de datos";
	delete db;
}

bool DataBase::ok() {
	/**Devuelve true si el status de la base de datos es ok**/
	return this->st.ok();
}
;

bool DataBase::put(DBtuple& tuple) {
	/**Registro la tupla en la base de datos.**/
	st = db->Put(WriteOptions(), tuple.key, tuple.value);
	return ok();
}
bool DataBase::get(DBtuple& tuple) {
	/**Busco un registro de la base de datos que tenga como key el valor pasado por parametro y lo devuelvo en la misma tupla.**/
	st = db->Get(ReadOptions(), tuple.key, &tuple.value);
	return ok();
}

string DataBase::status() {
	/**Devuelvo el estado de la base de datos**/
	return st.ToString();
}
void DataBase::logStatus() {
	/**Loggeo el status de la base de datos**/
	if (this->ok()) {
		LOG(INFO)<< status();
		return;
	}
	LOG(FATAL)<<status();
}
bool DataBase::delete_(DBtuple& tuple) {
	/**Borra un registro con el key que le pasan en la tuple de la base de datos**/
	st = db->Delete(WriteOptions(), tuple.key);
	return ok();
}
bool DataBase::deleteAll() {
	/**Borra todos los registros de la base de datos**/
	DBtuple tuple;
	rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		tuple.key = it->key().ToString();
		this->delete_(tuple);
	}
	st = it->status();
	delete it;
	if (ok()){
		LOG(INFO)<< "Borro los registros anteriores de la  base de datos";
	}
	return ok();
}
