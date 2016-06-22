/*
 * Interest.cpp
 *
 *  Created on: May 25, 2016
 *      Author: ediaz
 */

#include "Interest.h"

Interest::Interest() {
	// TODO Auto-generated constructor stub

}
void Interest::changeInterest(string category,string value){
	this->category=category;
	this->value=value;
}
Json::Value Interest::getJsonValue(){
	Json::Value Interest;
	Interest["category"]=this->category;
	Interest["value"]=this->value;
	return Interest;
}
Interest::~Interest() {
	// TODO Auto-generated destructor stub
}

string Interest::getCategory(){
	return this->category;
}

void Interest::setCategory(string category){
	this->category = category;
}

string Interest::getValue(){
	return this->value;
}

void Interest::setValue(string value){
	this->value = value;
}
