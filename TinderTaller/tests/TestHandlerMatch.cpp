#include "../include/gtest/gtest.h"
#include "../include/HandlerMatch.h"
#include "../include/ClientServiceMock.h"
#include "../include/TokenAuthentificatorMock.h"
TEST(HandlerMatch,isHandler) {
	JsonParser jsonParser;
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	shared_ptr<ClientServiceMock>clientServ (new ClientServiceMock());
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	shared_ptr<GcmClient> gcmClient(new GcmClient(clientServ));
	HandlerMatch* handler=new HandlerMatch(db,tokenAuth,sharedClient,gcmClient);
	http_message* hm = new http_message;
	hm->uri.p="/match/";
	hm->uri.len=strlen("/match/");
	EXPECT_TRUE(handler->isHandler(hm));
	delete hm;
	delete handler;
}
TEST(HandlerMatch,postMatch) {
	JsonParser jsonParser;
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	shared_ptr<ClientServiceMock>clientServ (new ClientServiceMock());
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	shared_ptr<GcmClient> gcmClient(new GcmClient(clientServ));
	HandlerMatch* handler=new HandlerMatch(db,tokenAuth,sharedClient,gcmClient);
	http_message* hm = new http_message;
	string mail="andy@yahoo.com";
	Json::Value val;
	Json::Value user;
	string anotherMail="eli@yahoo.com";
	val["email"]=anotherMail;
	std::string jsonIdString=jsonParser.valueToString(val);
	hm->body.p=jsonIdString.c_str();
	hm->body.len=jsonIdString.size();
	hm->method.p="POST";
	hm->method.len=4;
	hm->header_names[2].p="Authorization";
	hm->header_names[2].len=strlen("Authorization");
	hm->header_values[2].p=mail.c_str();
	hm->header_values[2].len=mail.size();
	hm->uri.p="/match/";
	hm->uri.len=strlen("/match/");
	DBtuple tpId(mail+"_id","1");
	EXPECT_TRUE(db->put(tpId));
	DBtuple anotherTpId(anotherMail+"_id","2");
	EXPECT_TRUE(db->put(anotherTpId));
	msg_t msg=handler->handleMsg(hm);
	EXPECT_TRUE(msg.status==StatusCode::OK);
	delete hm;
	delete handler;
}
