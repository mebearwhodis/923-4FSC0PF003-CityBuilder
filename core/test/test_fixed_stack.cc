#include <containers/fixed_stack.h>
#include <gtest/gtest.h>

class FixedStackFixture : public ::testing::TestWithParam<std::pair<core::FixedStack<int, 10>, std::vector<int>>>
{

};

//Test case for Push and Top functions
TEST_P(FixedStackFixture, PushAndTop) {
    auto [stack, vector] = GetParam();
    for (auto value : vector)
    {
        stack.Push(value);
    }

    //Ensure Top() throws an exception on an empty stack
    if (!vector.empty()) {
        EXPECT_EQ(stack.Top(), vector.back());
    }
    else {
        EXPECT_THROW(stack.Top(), std::out_of_range);
    }
}

//Test case for Pop function
TEST_P(FixedStackFixture, Pop) {
    auto [stack, vector] = GetParam();
    for (auto value : vector)
    {
        stack.Push(value);
    }

    //Ensure Pop() throws an exception on an empty stack
    if (!vector.empty()) {
        stack.Pop();
        vector.pop_back();

        //Ensure Top() throws an exception on an empty stack
        if (!vector.empty()) {
            EXPECT_EQ(stack.Top(), vector.back());
        }
        else {
            EXPECT_THROW(stack.Top(), std::out_of_range);
        }
    }
    else {
        EXPECT_THROW(stack.Pop(), std::out_of_range);
    }
}

//Test case for vectors bigger than FixedStack size
TEST_P(FixedStackFixture, Overflow) {
    auto [stack, vector] = GetParam();
    for (int i = 0; i < 10; i++)
    {
        stack.Push(0);
    }

    //Now attempt to Push one more element to check if overflow error is thrown
    EXPECT_THROW(stack.Push(0), std::overflow_error);
}


INSTANTIATE_TEST_SUITE_P(Numbers, FixedStackFixture,
    testing::Values(
        std::make_pair(core::FixedStack<int, 10>(), std::vector<int>{1, 4, 5, 123, 0, 3, -1}),
        std::make_pair(core::FixedStack<int, 10>(), std::vector<int>{5, 123, 3, -1}),
        std::make_pair(core::FixedStack<int, 10>(), std::vector<int>{})
    )
);