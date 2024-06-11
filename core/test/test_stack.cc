#include <containers/stack.h>
#include <gtest/gtest.h>
#include <numeric>  // For std::iota

class StackFixture : public ::testing::TestWithParam<std::pair<core::Stack<int>, std::vector<int>>>
{
};

// Test case for Push and Top functions
TEST_P(StackFixture, PushAndTop) {
    auto [stack, vector] = GetParam();
    for (auto value : vector)
    {
        stack.Push(value);
    }

    // Ensure Top() throws an exception on an empty stack
    if (!vector.empty()) {
        EXPECT_EQ(stack.Top(), vector.back());
    }
    else {
        EXPECT_THROW(stack.Top(), std::out_of_range);
    }
}

// Test case for Pop function
TEST_P(StackFixture, Pop) {
    auto [stack, vector] = GetParam();
    for (auto value : vector)
    {
        stack.Push(value);
    }

    // Ensure Pop() throws an exception on an empty stack
    if (!vector.empty()) {
        stack.Pop();
        vector.pop_back();

        // Ensure Top() throws an exception on an empty stack
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

// Test case for checking capacity changes
TEST_P(StackFixture, CapacityChange) {
    auto [stack, vector] = GetParam();

    // Push elements until the stack exceeds its initial capacity
    std::vector<int> large_vector(100);
    std::iota(large_vector.begin(), large_vector.end(), 0); // Fill with 0, 1, 2, ..., 99

    for (auto value : large_vector) {
        stack.Push(value);
    }

    // Check if the stack size matches the number of pushed elements
    EXPECT_EQ(stack.Size(), large_vector.size());

    // Check if elements are in the correct order
    for (int i = large_vector.size() - 1; i >= 0; --i) {
        EXPECT_EQ(stack.Top(), large_vector[i]);
        stack.Pop();
    }

    // Ensure the stack is empty
    EXPECT_THROW(stack.Top(), std::out_of_range);
    EXPECT_THROW(stack.Pop(), std::out_of_range);
}

INSTANTIATE_TEST_SUITE_P(Numbers, StackFixture,
    testing::Values(
        std::make_pair(core::Stack<int>(), std::vector<int>{1, 4, 5, 123, 0, 3, -1}),
        std::make_pair(core::Stack<int>(), std::vector<int>{5, 123, 3, -1}),
        std::make_pair(core::Stack<int>(), std::vector<int>{})
    )
);
