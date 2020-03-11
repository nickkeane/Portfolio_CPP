#include "ToDoCore/ToDo.h"

#include <string>
using std::string;
#include <iostream>
using std::cin;

#include <gmock/gmock.h>
#include <gtest/gtest.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv); // Issue is most likey here, probably a string or linkage issue. -static-libgcc -static-libstdc++ ?
    
    int res = RUN_ALL_TESTS();
    return res;
}

namespace ToDoCore {
    namespace testing {
        class ToDoTest : public ::testing::Test {
            protected:
                ToDoTest() {}
                ~ToDoTest() {}

                void SetUp() override {}
                void TearDown() override {}

                ToDo list;

                enum { taskCount = 3ULL };
                static const string tasks[taskCount];
        };

        const string ToDoTest::tasks[ToDoTest::taskCount] = {"write code", "compile", "test"};

        TEST_F(ToDoTest, ctor_createEmptyList) {
            EXPECT_EQ(list.size(), (size_t)0ULL);
        }

        
        TEST_F(ToDoTest, addTask_threeTimes_sizeIsThree) {
            list.addTask(tasks[0]);
            list.addTask(tasks[1]);
            list.addTask(tasks[2]);

            EXPECT_EQ(list.size(), taskCount);
        }

        TEST_F(ToDoTest, getTask_withOneTask_returnsCorrectString) {
            list.addTask(tasks[0]);

            ASSERT_EQ(list.size(), 1ULL);
            EXPECT_EQ(list.getTask(0), tasks[0]);
        }

        TEST_F(ToDoTest, getTask_withThreeTests_returnsCorrectStringForEachIndex) {
            list.addTask(tasks[0]);
            list.addTask(tasks[1]);
            list.addTask(tasks[2]);

            ASSERT_EQ(list.size(), taskCount);
            EXPECT_EQ(list.getTask(0), tasks[0]);
            EXPECT_EQ(list.getTask(1), tasks[1]);
            EXPECT_EQ(list.getTask(2), tasks[2]);
        }
    }
}