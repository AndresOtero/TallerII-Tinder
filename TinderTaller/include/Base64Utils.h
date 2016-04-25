/*
 * Base64Utils.h
 *
 *  Created on: 24 de abr. de 2016
 *      Author: andres
 */
//Aclaracion no es nuestro codigo
//Fuente: 	http://www.adp-gmbh.ch/cpp/common/base64.html
#include <string>


#ifndef SRC_BASE64UTILS_H_
#define SRC_BASE64UTILS_H_

class Base64Utils {
public:
	Base64Utils();
	std::string base64_encodeString(std::string);
	std::string base64_decode(std::string const& s);
	virtual ~Base64Utils();
private:
	std::string base64_encode(unsigned char const* , unsigned int len);

};

#endif /* SRC_BASE64UTILS_H_ */
