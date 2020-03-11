#include <iostream>
using std::cout;
using std::endl;

#include <gtest/gtest.h>
using testing::Test;
using testing::InitGoogleTest;

#include "sodiumpp.h"
using sodiumpp::SodiumContext;

namespace sodiumpp_test {
    class SodiumContextTest : public Test {
        protected:
            sodiumpp::SodiumContext* ctx;

            virtual void SetUp() {
                ctx = SodiumContext::instance();
            }

            virtual void TearDown() {

            }
    };

    TEST_F(SodiumContextTest, ExistanceTest) {
        ASSERT_NE(ctx, nullptr);
    }
}

int main(int /*argc*/, char** /*argv*/) {
    InitGoogleTest();
    return RUN_ALL_TESTS();
}