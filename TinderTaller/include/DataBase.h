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
using namespace rocksdb;
using namespace std;

#ifndef DATABASE_H_
#define DATABASE_H_

class DataBase {
	 DB* db;
	 Options options;
	 Status st;

public:
	DataBase();
	bool put(string key,string value);
	bool ok();
	bool get(string key , string* value);
	bool delete_(string key);
	string status();
	virtual ~DataBase();
};

#endif /* DATABASE_H_ */
