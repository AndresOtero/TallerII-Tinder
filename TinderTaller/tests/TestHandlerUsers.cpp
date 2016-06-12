#include "../include/gtest/gtest.h"
#include "../include/HandlerUsers.h"
#include "../include/ClientServiceMock.h"
#include "../include/TokenAuthentificatorMock.h"
TEST(HandlerUsers,isHandler) {
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificator> tokenAuth(new TokenAuthentificator(db));
	ClientServiceMock *clientServ =new ClientServiceMock();
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	HandlerUsers* handler=new HandlerUsers(db,tokenAuth,sharedClient);
	http_message* hm = new http_message;
	hm->uri.p="/users/";
	hm->uri.len=strlen("/users/");

	EXPECT_TRUE( handler->isHandler(hm));
	delete handler;
	delete hm;
}
TEST(HandlerUsers,postUser) {
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	ClientServiceMock *clientServ =new ClientServiceMock();
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	HandlerUsers* handler=new HandlerUsers(db,tokenAuth,sharedClient);
	http_message* hm = new http_message;
	hm->uri.p="/users/";
	hm->uri.len=strlen("/users/");
	JsonParser jsonParser;
	Json::Value val;
	Json::Value user;
	string pass="pass";
	user["password"]=pass;
	string mail="andy@yahoo.com";
	user["email"]=mail;
	string gmcId="aaa";
	user["gcm_registration_id"]=gmcId;
	val["user"]=user;
	std::string jsonIdString=jsonParser.valueToString(val);
	hm->body.p=jsonIdString.c_str();
	hm->body.len=jsonIdString.size();
	hm->method.p="POST";
	hm->method.len=4;
	msg_t msg=handler->handleMsg(hm);
	EXPECT_TRUE(msg.status==StatusCode::CREATED);
	Json::Value jsonReturn=jsonParser.stringToValue(msg.body);
	EXPECT_TRUE(jsonReturn["token"].asString()==mail);
	EXPECT_TRUE(jsonReturn["user"]["email"].asString()==mail);
	EXPECT_TRUE(jsonReturn["user"]["gcm_registration_id"].asString()==gmcId);

	delete handler;
	delete hm;
}
