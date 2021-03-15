#include "common/databaseModule/databaseInterface.h"
#include "common/databaseModule/databaseManager.h"
#include "common/utilityModule/stringUtility.h"
//#include "databasesModule/coursesDatabase.h"
#include "cocos2d.h"
#include "databasesModule/ipaDatabase.h"
#include <gtest/gtest.h>

using namespace common::utilityModule;
using namespace common::databaseModule;
using namespace cardsApp::databasesModule;

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace DBTests::test {
    class TempClass : public testing::Test {};
}// namespace DBTests::test
using namespace DBTests::test;

TEST_F(TempClass, cocos2dSimpleIntegrationTest) {
    auto size1 = cocos2d::Size(1.f, 2.f);
    auto size2 = cocos2d::Size(2.f, 1.f);
    EXPECT_EQ(size1.width, size2.height);
    EXPECT_TRUE(size1.width != size2.width);
}

TEST_F(TempClass, commonStringUtilsTest) {
    EXPECT_EQ(stringUtility::capitalizeString("test room is awesome!"), std::string("Test room is awesome!"));
    EXPECT_EQ(stringUtility::toLowerString("Test RoOm IS aweSome!"), std::string("test room is awesome!"));
}

TEST_F(TempClass, cardsAppDatabaseTest) {
    GET_DATABASE_MANAGER().registerDatabase({ "ipaDb", "properties/database/dictionary/db.json" },
                                            new cardsApp::databasesModule::ipaDatabase());
    GET_DATABASE_MANAGER().executeLoadData();
    auto ipaDb = GET_DATABASE_MANAGER().getDatabase<ipaDatabase>("ipaDb");
    EXPECT_TRUE(ipaDb->isLoaded());
}