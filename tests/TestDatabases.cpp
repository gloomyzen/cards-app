#include "../src/common/utilityModule/stringUtility.h"
#include "cocos2d.h"
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace DBTests::test {
    class TempClass : public testing::Test {};
}
using namespace DBTests::test;

TEST_F(TempClass, cocos2dSimpleIntegrationTest) {
    auto size1 = cocos2d::Size(1.f, 2.f);
    auto size2 = cocos2d::Size(2.f, 1.f);
    EXPECT_EQ(size1.width, size2.height);
    EXPECT_TRUE(size1.width != size2.width);
}

TEST_F(TempClass, cardsAppStringUtilsTest) {
    using namespace common::utilityModule;
    EXPECT_EQ(stringUtility::capitalizeString("test room is awesome!"), std::string("Test room is awesome!"));
    EXPECT_EQ(stringUtility::toLowerString("Test RoOm IS aweSome!"), std::string("test room is awesome!"));
}