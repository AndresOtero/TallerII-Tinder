#include "../include/gtest/gtest.h"
#include "../include/HandlerChat.h"
#include "../include/HandlerMatch.h"

#include "../include/ClientServiceMock.h"
#include "../include/TokenAuthentificatorMock.h"
TEST(HandlerChat,isHandler) {
	JsonParser jsonParser;
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	shared_ptr<ClientServiceMock>clientServ (new ClientServiceMock());
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	shared_ptr<GcmClient> gcmClient(new GcmClient(clientServ));
	HandlerChat* handler=new HandlerChat(db,tokenAuth,sharedClient,gcmClient);
	http_message* hm = new http_message;
	hm->uri.p="/chat/";
	hm->uri.len=strlen("/chat/");
	EXPECT_TRUE(handler->isHandler(hm));
	delete hm;
	delete handler;
}

TEST(HandlerChat,postChat) {
	JsonParser jsonParser;
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	shared_ptr<ClientServiceMock>clientServ (new ClientServiceMock());
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	shared_ptr<GcmClient> gcmClient(new GcmClient(clientServ));
	HandlerChat* handler=new HandlerChat(db,tokenAuth,sharedClient,gcmClient);
	HandlerMatch* handlerMatch=new HandlerMatch(db,tokenAuth,sharedClient,gcmClient);

	http_message* hm = new http_message;
	string mail="andy@yahoo.com";
	Json::Value val;
	Json::Value user;
	string anotherMail="eli@yahoo.com";
	val["To"]=anotherMail;
	val["message"]="Holis";
	std::string jsonIdString=jsonParser.valueToString(val);
	hm->body.p=jsonIdString.c_str();
	hm->body.len=jsonIdString.size();
	hm->method.p="POST";
	hm->method.len=4;
	hm->header_names[3].p="Authorization";
	hm->header_names[3].len=strlen("Authorization");
	hm->header_values[3].p=mail.c_str();
	hm->header_values[3].len=mail.size();
	Json::Value empty=Json::Value(Json::nullValue);
	DBtuple userChats(mail+"_chats",jsonParser.valueToString(empty));
	EXPECT_TRUE(db->put(userChats));
	DBtuple anotherUserChats(anotherMail+"_chats",jsonParser.valueToString(empty));
	EXPECT_TRUE(db->put(anotherUserChats));
	DBtuple tpId(mail+"_id","1");
	EXPECT_TRUE(db->put(tpId));
	DBtuple anotherTpId(anotherMail+"_id","1");
	EXPECT_TRUE(db->put(anotherTpId));
	DBtuple anotherToken("token_"+anotherMail,"1");
	EXPECT_TRUE(db->put(anotherToken));
	handlerMatch->saveNewChat(mail,anotherMail);
	msg_t msg=handler->handleMsg(hm);
	EXPECT_TRUE(msg.status==StatusCode::OK);
	delete hm;
	delete handler;
	delete handlerMatch;
}

TEST(HandlerChat,getAllChat) {
	JsonParser jsonParser;
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	shared_ptr<ClientServiceMock>clientServ (new ClientServiceMock());
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	shared_ptr<GcmClient> gcmClient(new GcmClient(clientServ));
	HandlerChat* handler=new HandlerChat(db,tokenAuth,sharedClient,gcmClient);
	HandlerMatch* handlerMatch=new HandlerMatch(db,tokenAuth,sharedClient,gcmClient);
	http_message* hm = new http_message;
	string mail="andy@yahoo.com";
	Json::Value val;
	Json::Value user;
	string anotherMail="eli@yahoo.com";
	val["To"]=anotherMail;
	val["message"]="Holis";
	std::string jsonIdString=jsonParser.valueToString(val);
	hm->body.p=jsonIdString.c_str();
	hm->body.len=jsonIdString.size();
	hm->method.p="POST";
	hm->method.len=4;
	hm->header_names[1].p="Authorization";
	hm->header_names[1].len=strlen("Authorization");
	hm->header_values[1].p=mail.c_str();
	hm->header_values[1].len=mail.size();
	Json::Value empty=Json::Value(Json::nullValue);
	DBtuple tpId(mail+"_id","1");
	EXPECT_TRUE(db->put(tpId));
	DBtuple anotherTpId(anotherMail+"_id","1");
	EXPECT_TRUE(db->put(anotherTpId));
	handlerMatch->saveNewChat(mail,anotherMail);
	msg_t msg=handler->handleMsg(hm);
	EXPECT_TRUE(msg.status==StatusCode::OK);
	hm->method.p="GET";
	hm->method.len=3;
	hm->uri.p="/chat/ HTTP";
	hm->uri.len=strlen("/chat/ HTTP");
	msg=handler->handleMsg(hm);
	EXPECT_TRUE(msg.status==StatusCode::OK);
	Json::Value jsonValueReturn=jsonParser.stringToValue(msg.body);

	delete hm;
	delete handler;
	delete handlerMatch;
}
TEST(HandlerChat,getIdChat) {
	JsonParser jsonParser;
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	shared_ptr<ClientServiceMock>clientServ (new ClientServiceMock());
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	shared_ptr<GcmClient> gcmClient(new GcmClient(clientServ));
	HandlerChat* handler=new HandlerChat(db,tokenAuth,sharedClient,gcmClient);
	HandlerMatch* handlerMatch=new HandlerMatch(db,tokenAuth,sharedClient,gcmClient);

	http_message* hm = new http_message;
	string mail="andy@yahoo.com";
	Json::Value val;
	Json::Value user;
	string anotherMail="eli@yahoo.com";
	val["To"]=anotherMail;
	val["message"]="Holis";
	std::string jsonIdString=jsonParser.valueToString(val);
	hm->body.p=jsonIdString.c_str();
	hm->body.len=jsonIdString.size();
	hm->method.p="POST";
	hm->method.len=4;
	hm->header_names[1].p="Authorization";
	hm->header_names[1].len=strlen("Authorization");
	hm->header_values[1].p=mail.c_str();
	hm->header_values[1].len=mail.size();
	handlerMatch->saveNewChat(mail,anotherMail);
	msg_t msg=handler->handleMsg(hm);
	EXPECT_TRUE(msg.status==StatusCode::OK);
	hm->method.p="GET";
	hm->method.len=3;
	hm->uri.p="/chat/0-10/";
	hm->uri.len=strlen("/chat/0-10/");
	msg=handler->handleMsg(hm);
	EXPECT_TRUE(msg.status==StatusCode::OK);
	Json::Value jsonValueReturn=jsonParser.stringToValue(msg.body);

	delete hm;
	delete handlerMatch;
	delete handler;
}

