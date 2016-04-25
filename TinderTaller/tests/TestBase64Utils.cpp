/*
 * TestBase64Utils.cpp
 *
 *  Created on: 24 de abr. de 2016
 *      Author: andres
 */
#include "../include/gtest/gtest.h"
#include "../include/Base64Utils.h"
using namespace std;

TEST(Base64Utils,encodeAndDecode) {
	Base64Utils base64Utils;
	string secret="Calle false 1234";
	string encoded =base64Utils.base64_encodeString(secret);
	EXPECT_EQ(encoded,string("Q2FsbGUgZmFsc2UgMTIzNA=="));//https://www.base64decode.org/
	string decoded =base64Utils.base64_decode(encoded);
	EXPECT_EQ(decoded,secret);
}

