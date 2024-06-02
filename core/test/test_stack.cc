#include <structures/stack.h>
#include <gtest/gtest.h>

class StackFixture : public ::testing::TestWithParam<std::pair<core::Stack<int>, std::vector<int>>>
{

};

// Test case for push and top functions
TEST_P(StackFixture, PushAndTop) {
    auto [stack, vector] = GetParam();
    for (auto value : vector)
    {
        stack.push(value);
    }

    if (!vector.empty()) {
        EXPECT_EQ(stack.top(), vector.back());
    }
    else {
        EXPECT_THROW(stack.top(), std::underflow_error); //Ensure top() throws an exception on an empty stack
    }
}

// Test case for pop function
TEST_P(StackFixture, Pop) {
    auto [stack, vector] = GetParam();
    for (auto value : vector)
    {
        stack.push(value);
    }

    if (!vector.empty()) {
        stack.pop();
        vector.pop_back();
        if (!vector.empty()) {
            EXPECT_EQ(stack.top(), vector.back());
        }
        else {
            EXPECT_THROW(stack.top(), std::underflow_error); //Ensure top() throws an exception on an empty stack
        }
    }
    else {
        EXPECT_THROW(stack.pop(), std::underflow_error); //Ensure pop() throws an exception on an empty stack
    }
}


INSTANTIATE_TEST_SUITE_P(Numbers, StackFixture,
    testing::Values(
        std::make_pair(core::Stack<int>(), std::vector<int>{1, 4, 5, 123, 0, 3, -1}),
        std::make_pair(core::Stack<int>(), std::vector<int>{5, 123, 3, -1}),
        std::make_pair(core::Stack<int>(), std::vector<int>{})
    )
);