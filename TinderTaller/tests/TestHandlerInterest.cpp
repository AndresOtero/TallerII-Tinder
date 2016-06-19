#include "../include/gtest/gtest.h"
#include "../include/HandlerInterest.h"
#include "../include/ClientServiceMock.h"
#include "../include/TokenAuthentificatorMock.h"
TEST(HandlerInterest,isHandler) {
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	shared_ptr<ClientServiceMock>clientServ (new ClientServiceMock());
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	HandlerInterest* handler=new HandlerInterest(db,tokenAuth,sharedClient);
	http_message* hm = new http_message;
	hm->uri.p="/interests/";
	hm->uri.len=strlen("/interests/");
	EXPECT_TRUE( handler->isHandler(hm));
	delete handler;
	delete hm;
}
TEST(HandlerInterest,getIntersts) {
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	shared_ptr<ClientServiceMock>clientServ (new ClientServiceMock());
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	HandlerInterest* handler=new HandlerInterest(db,tokenAuth,sharedClient);
	http_message* hm = new http_message;
	hm->uri.p="/interests/";
	hm->uri.len=strlen("/interests/");
	hm->method.p="GET";
	hm->method.len=strlen("GET");

	msg_t msg=handler->handleMsg(hm);
	EXPECT_TRUE(msg.status=StatusCode::OK);
	EXPECT_TRUE(msg.body=="Intereses");
	delete handler;
	delete hm;
}
TEST(HandlerInterest,postIntersts) {
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	shared_ptr<ClientServiceMock>clientServ (new ClientServiceMock());
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	HandlerInterest* handler=new HandlerInterest(db,tokenAuth,sharedClient);
	http_message* hm = new http_message;
	hm->uri.p="/interests/";
	hm->uri.len=strlen("/interests/");
	hm->method.p="POST";
	hm->method.len=strlen("POST");
	hm->body.p="{interes}";
	hm->body.len=strlen("{interes}");
	msg_t msg=handler->handleMsg(hm);
	EXPECT_TRUE(msg.status=StatusCode::CREATED);
	EXPECT_TRUE(msg.body=="{interes}");
	delete handler;
	delete hm;
}
