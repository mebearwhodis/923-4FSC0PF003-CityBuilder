#include <structures/queue.h>
#include <gtest/gtest.h>

class QueueFixture : public ::testing::TestWithParam<std::pair<core::Queue<int>, std::vector<int>>>
{

};

//Test case for push and front functions
TEST_P(QueueFixture, PushAndFront) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.push(value);
    }

    //Ensure front() throws an exception on an empty vector
    if (!vector.empty()) {
        EXPECT_EQ(queue.front(), vector.front());
    }
    else {
        EXPECT_THROW(queue.front(), std::underflow_error); 
    }
}

//Test case for pop function
TEST_P(QueueFixture, Pop) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.push(value);
    }

    //Ensure pop() throws an exception on an empty queue
    if (!vector.empty()) {
        queue.pop();
        vector.erase(vector.begin());

        //Ensure front() throws an exception on an empty vector
        if (!vector.empty()) {
            EXPECT_EQ(queue.front(), vector.front());
        }
        else {
            EXPECT_THROW(queue.front(), std::underflow_error); 
        }
    }
    else {
        EXPECT_THROW(queue.pop(), std::underflow_error); 
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

//Test case for push and front functions
TEST_P(FixedQueueFixture, PushAndFront) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.push(value);
    }

    //Ensure front() throws an exception on an empty vector
    if (!vector.empty()) {
        EXPECT_EQ(queue.front(), vector.front());
    }
    else {
        EXPECT_THROW(queue.front(), std::underflow_error); 
    }
}

//Test case for pop function
TEST_P(FixedQueueFixture, Pop) {
    auto [queue, vector] = GetParam();
    for (auto value : vector)
    {
        queue.push(value);
    }

    //Ensure pop() throws an exception on an empty queue
    if (!vector.empty()) {
        queue.pop();
        vector.erase(vector.begin());

        //Ensure front() throws an exception on an empty vector
        if (!vector.empty()) {
            EXPECT_EQ(queue.front(), vector.front());
        }
        else {
            EXPECT_THROW(queue.front(), std::underflow_error); 
        }
    }
    else {
        EXPECT_THROW(queue.pop(), std::underflow_error); 
    }
}

//Test case for vectors bigger than FixedQueue size
TEST_P(FixedQueueFixture, Overflow) {
    auto [queue, vector] = GetParam();
    for (int i = 0; i < 10; i++)
    {
            queue.push(0);
    }

    //Now attempt to push one more element to check if overflow error is thrown
    EXPECT_THROW(queue.push(0), std::overflow_error);
}


INSTANTIATE_TEST_SUITE_P(Numbers, FixedQueueFixture,
    testing::Values(
        std::make_pair(core::FixedQueue<int, 10>(), std::vector<int>{1, 4, 5, 123, 0, 3, -1}),
        std::make_pair(core::FixedQueue<int, 10>(), std::vector<int>{5, 123, 3, -1}),
        std::make_pair(core::FixedQueue<int, 10>(), std::vector<int>{})
    )
);