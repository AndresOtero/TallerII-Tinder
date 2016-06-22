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
	/**Cambio la categoria y el valor del interes**/
	this->category=category;
	this->value=value;
}
Json::Value Interest::getJsonValue(){
	/**Devuelvo al interes como un json value**/
	Json::Value Interest;
	Interest["category"]=this->category;
	Interest["value"]=this->value;
	return Interest;
}
Interest::~Interest() {
/**Destructor del interes**/
	}

string Interest::getCategory(){
	/**Devuelvo la categoria del interes**/
	return this->category;
}

void Interest::setCategory(string category){
	/**Setteo la categoria del interes**/

	this->category = category;
}

string Interest::getValue(){
	/**Devuelvo el valor del interes**/

	return this->value;
}

void Interest::setValue(string value){
	/**Setteo  el valor del interes**/

	this->value = value;
}
