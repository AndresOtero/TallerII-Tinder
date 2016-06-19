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
TEST(HandlerUsers,delete_) {
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
	hm->method.p="DELETE";
	hm->method.len=strlen("DELETE");
	string uriDelete="/users/"+mail+"/";
	hm->uri.p=uriDelete.c_str();
	hm->uri.len=uriDelete.size();
	msg=handler->handleMsg(hm);
	EXPECT_TRUE(msg.status==StatusCode::OK);
	delete handler;
	delete hm;
}
TEST(HandlerUsers,getUser) {
	JsonParser jsonParser;
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	ClientServiceMock *clientServ =new ClientServiceMock();
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	HandlerUsers* handler=new HandlerUsers(db,tokenAuth,sharedClient);
	http_message* hm = new http_message;
	string mail="andy@yahoo.com";
	DBtuple userId(mail+"_id","1");
	EXPECT_TRUE(db->put(userId));
	hm->method.p="GET";
	hm->method.len=strlen("GET");
	string uriGet="/users/"+mail+"/";
	hm->uri.p=uriGet.c_str();
	hm->uri.len=uriGet.size();
	msg_t msg = handler->handleMsg(hm);
	EXPECT_TRUE(msg.status == StatusCode::OK);
	Json::Value jsonReturn = jsonParser.stringToValue(msg.body);
	EXPECT_TRUE(jsonReturn["user"]["email"].asString() == mail);
	EXPECT_TRUE(jsonReturn["user"]["password"].asString() == "pass");
	delete handler;
	delete hm;
}
TEST(HandlerUsers,putUser) {
	JsonParser jsonParser;
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	ClientServiceMock *clientServ =new ClientServiceMock();
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	HandlerUsers* handler=new HandlerUsers(db,tokenAuth,sharedClient);
	http_message* hm = new http_message;
	Json::Value val;
	Json::Value user;
	string mail="andy@yahoo.com";
	DBtuple userId(mail+"_id","1");
	EXPECT_TRUE(db->put(userId));
	hm->method.p="PUT";
	hm->method.len=strlen("PUT");
	string uriGet="/users/"+mail+"/ hhTTTTPPPP";
	hm->uri.p=uriGet.c_str();
	hm->uri.len=uriGet.size();
	user["sex"]="H";
	user["gcm_registration_id"]="gcm";
	user["password"]="pass";
	val["user"]=user;
	std::string jsonIdString=jsonParser.valueToString(val);
	hm->body.p=jsonIdString.c_str();
	hm->body.len=jsonIdString.size();
	msg_t msg = handler->handleMsg(hm);
	EXPECT_TRUE(msg.status == StatusCode::OK);
	//Json::Value jsonReturn = jsonParser.stringToValue(msg.body);
	//EXPECT_TRUE(jsonReturn["user"]["email"].asString() == mail);
	//EXPECT_TRUE(jsonReturn["user"]["password"].asString() == "pass");
	delete handler;
	delete hm;
}
TEST(HandlerUsers,putPhoto) {
	JsonParser jsonParser;
	shared_ptr<DataBase> db(new DataBase("./DBTest/", true, true));
	shared_ptr<TokenAuthentificatorMock> tokenAuth(new TokenAuthentificatorMock());
	ClientServiceMock *clientServ =new ClientServiceMock();
	shared_ptr<SharedClient> sharedClient(new SharedClient(clientServ));
	HandlerUsers* handler=new HandlerUsers(db,tokenAuth,sharedClient);
	http_message* hm = new http_message;
	Json::Value val;
	Json::Value user;
	string mail="andy@yahoo.com";
	DBtuple userId(mail+"_id","1");
	EXPECT_TRUE(db->put(userId));
	hm->method.p="PUT";
	hm->method.len=strlen("PUT");
	string uriPut="/users/"+mail+"/photo/";
	hm->uri.p=uriPut.c_str();
	hm->uri.len=uriPut.size();
	user["photo"]="H";
	val["user"]=user;
	std::string jsonIdString=jsonParser.valueToString(val);
	hm->body.p=jsonIdString.c_str();
	hm->body.len=jsonIdString.size();
	msg_t msg = handler->handleMsg(hm);
	EXPECT_TRUE(msg.status == StatusCode::OK);
	Json::Value jsonReturn = jsonParser.stringToValue(msg.body);
	EXPECT_TRUE(jsonReturn["user"]["photo"].asString() == "H");

	delete handler;
	delete hm;
}
