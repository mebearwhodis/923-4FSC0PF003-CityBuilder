#include <structures/queue.h>
#include <gtest/gtest.h>

class QueueFixture : public ::testing::TestWithParam<std::pair<core::Queue<int>, std::vector<int>>>
{

};

//TODO: Tests for when capacity is modified (are things still in order, etc.)
//Test case for Push and Front functions
TEST_P(QueueFixture, PushAndFront) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.Push(value);
    }

    //Ensure Front() throws an exception on an empty vector
    if (!vector.empty()) {
        EXPECT_EQ(queue.Front(), vector.front());
    }
    else {
        EXPECT_THROW(queue.Front(), std::underflow_error); 
    }
}

//Test case for Pop function
TEST_P(QueueFixture, Pop) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.Push(value);
    }

    //Ensure Pop() throws an exception on an empty queue
    if (!vector.empty()) {
        queue.Pop();
        vector.erase(vector.begin());

        //Ensure Front() throws an exception on an empty vector
        if (!vector.empty()) {
            EXPECT_EQ(queue.Front(), vector.front());
        }
        else {
            EXPECT_THROW(queue.Front(), std::underflow_error); 
        }
    }
    else {
        EXPECT_THROW(queue.Pop(), std::underflow_error); 
    }
}


INSTANTIATE_TEST_SUITE_P(Numbers, QueueFixture,
    testing::Values(
        std::make_pair(core::Queue<int>(), std::vector<int>{1, 4, 5, 123, 0, 3, -1}),
        std::make_pair(core::Queue<int>(), std::vector<int>{5, 123, 3, -1}),
        std::make_pair(core::Queue<int>(), std::vector<int>{})
        )
);


class FixedQueueFixture : public ::testing::TestWithParam<std::pair<core::FixedQueue<int, 10>, std::vector<int>>>
{

};

//Test case for Push and Front functions
TEST_P(FixedQueueFixture, PushAndFront) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.Push(value);
    }

    //Ensure Front() throws an exception on an empty vector
    if (!vector.empty()) {
        EXPECT_EQ(queue.Front(), vector.front());
    }
    else {
        EXPECT_THROW(queue.Front(), std::underflow_error); 
    }
}

//Test case for Pop function
TEST_P(FixedQueueFixture, Pop) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.Push(value);
    }

    //Ensure Pop() throws an exception on an empty queue
    if (!vector.empty()) {
        queue.Pop();
        vector.erase(vector.begin());

        //Ensure Front() throws an exception on an empty vector
        if (!vector.empty()) {
            EXPECT_EQ(queue.Front(), vector.front());
        }
        else {
            EXPECT_THROW(queue.Front(), std::underflow_error); 
        }
    }
    else {
        EXPECT_THROW(queue.Pop(), std::underflow_error); 
    }
}

//Test case for vectors bigger than FixedQueue size
TEST_P(FixedQueueFixture, Overflow) {
    auto [queue, vector] = GetParam();
    for (int i = 0; i < 10; i++)
    {
            queue.Push(0);
    }

    //Now attempt to Push one more element to check if overflow error is thrown
    EXPECT_THROW(queue.Push(0), std::overflow_error);
}


INSTANTIATE_TEST_SUITE_P(Numbers, FixedQueueFixture,
    testing::Values(
        std::make_pair(core::FixedQueue<int, 10>(), std::vector<int>{1, 4, 5, 123, 0, 3, -1}),
        std::make_pair(core::FixedQueue<int, 10>(), std::vector<int>{5, 123, 3, -1}),
        std::make_pair(core::FixedQueue<int, 10>(), std::vector<int>{})
    )
);