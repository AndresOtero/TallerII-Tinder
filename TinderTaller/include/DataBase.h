/*
 * DataBase.h
 *
 *  Created on: 1 de abr. de 2016
 *      Author: andres
 */
#include "../include/rocksdb/db.h"
#include "../include/rocksdb/slice.h"
#include "../include/rocksdb/options.h"
#include "easylogging++.h"
#include <string>
#include "../include/rocksdb/status.h"
using namespace rocksdb;
using namespace std;

#ifndef DATABASE_H_
#define DATABASE_H_

typedef struct DBtuple {
   string key;
   string value;
   DBtuple(string key,string value){
	   this->key=key;
	   this->value=value;
   }
   DBtuple();
   DBtuple(string key){
	   this->key=key;
   }

}DBtuple_t;

class DataBase {
	 DB* db;
	 Options options;
	 Status st;
private:
		string status();
public:
	DataBase(const std::string& db_path, bool create_if_missing, bool clean);
	bool put(DBtuple& tuple);
	bool ok();
	bool get(DBtuple& tuple);
	bool delete_(DBtuple& tuple);
	bool deleteAll();
	void logStatus();
	virtual ~DataBase();
};

#endif /* DATABASE_H_ */
