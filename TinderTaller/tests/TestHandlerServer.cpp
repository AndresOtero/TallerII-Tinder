#include "../include/gtest/gtest.h"
#include "../include/HandlerServer.h"
#include "../include/mongoose.h"
#include <vector>
#include <iostream>


TEST(HandlerServer,handleBad) {
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, false));
	HandlerServer* handlerServer=new HandlerServer(db);
	http_message* hm = new http_message;
	hm->uri.p="/jajaja/";
	hm->uri.len=8;
	msg_t msg=handlerServer->handler(hm);
	EXPECT_TRUE(msg.status=StatusCode::BAD_REQUEST);
	delete hm;
	delete handlerServer;
}
