#include "../include/gtest/gtest.h"
#include "../include/Configuration.h"
using namespace std;

TEST(Configuration,get) {
	Configuration::setPath("./config/testConfig.Json");
	Configuration* config = Configuration::getConfiguration().get();
	string version=config->getStringAttribute("version");
	EXPECT_TRUE(version=="1");
}
