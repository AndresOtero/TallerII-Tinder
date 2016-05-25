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
