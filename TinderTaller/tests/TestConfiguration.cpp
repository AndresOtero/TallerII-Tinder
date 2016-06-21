#include "../include/gtest/gtest.h"
#include "../include/Configuration.h"
using namespace std;

TEST(Configuration,getString) {
	Configuration::setPath("./config/testConfig.Json");
	Configuration* config = Configuration::getConfiguration().get();
	string version=config->getStringAttribute("version");
	EXPECT_TRUE(version=="1");
}
TEST(Configuration,getBool) {
	Configuration::setPath("./config/testConfig.Json");
	Configuration* config = Configuration::getConfiguration().get();
	bool killAll=config->getBooleanAttribute("killAll");
	EXPECT_TRUE(killAll);
}
