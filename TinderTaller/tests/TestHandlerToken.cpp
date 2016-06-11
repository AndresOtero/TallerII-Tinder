#include "../include/gtest/gtest.h"
#include "../include/HandlerToken.h"
#include "../include/ClientServiceMock.h"
TEST(HandlerToken,isHandler) {
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificator> tokenAuth(new TokenAuthentificator(db));
	ClientServiceMock *clientServ =new ClientServiceMock();
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	HandlerToken* handler=new HandlerToken(db,tokenAuth,sharedClient);
	http_message* hm = new http_message;
	hm->uri.p="/token/";
	hm->uri.len=5;
	EXPECT_TRUE( handler->isHandler(hm));
	delete handler;
	delete hm;
}
TEST(HandlerToken,post) {
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificator> tokenAuth(new TokenAuthentificator(db));
	ClientServiceMock *clientServ =new ClientServiceMock();
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	HandlerToken* handler=new HandlerToken(db,tokenAuth,sharedClient);
	http_message* hm = new http_message;
	JsonParser jsonParser;
	Json::Value val;
	Json::Value user;
	string pass="pass";
	user["password"]=pass;
	string mail="andy@yahoo.com";
	user["email"]=mail;
	val["user"]=user;
	std::string jsonIdString=jsonParser.valueToString(val);
	hm->body.p=jsonIdString.c_str();
	hm->body.len=jsonIdString.size();

	DBtuple tpPass(mail+"_pass",pass);
	bool okPass=db->put(tpPass);
	DBtuple tpId(mail+"_id","1");
	bool okId=db->put(tpId);
	hm->uri.p="/token/ HTTP...";
	hm->uri.len=5;
	hm->method.p="POST";
	hm->method.len=4;
	msg_t msg= handler->handleMsg(hm);
	EXPECT_TRUE(msg.status==StatusCode::CREATED);
	delete handler;
	delete hm;
}
TEST(HandlerToken,singin) {
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificator> tokenAuth(new TokenAuthentificator(db));
	ClientServiceMock *clientServ =new ClientServiceMock();
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	HandlerToken* handler=new HandlerToken(db,tokenAuth,sharedClient);
	http_message* hm = new http_message;
	JsonParser jsonParser;
	Json::Value val;
	Json::Value user;
	string pass="pass";
	user["password"]=pass;
	string mail="andy@yahoo.com";
	user["email"]=mail;
	val["user"]=user;
	std::string jsonIdString=jsonParser.valueToString(val);
	hm->body.p=jsonIdString.c_str();
	hm->body.len=jsonIdString.size();

	DBtuple tpPass(mail+"_pass",pass);
	bool okPass=db->put(tpPass);
	DBtuple tpId(mail+"_id","1");
	bool okId=db->put(tpId);
	hm->uri.p="/token/singin/ HTTP...";
	hm->uri.len=5;
	hm->method.p="POST";
	hm->method.len=4;
	msg_t msg= handler->handleMsg(hm);
	EXPECT_TRUE(msg.status==StatusCode::CREATED);
	delete handler;
	delete hm;
}
