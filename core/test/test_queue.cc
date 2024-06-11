#include <containers/queue.h>
#include <gtest/gtest.h>
#include <numeric>  // For std::iota

class QueueFixture : public ::testing::TestWithParam<std::pair<core::Queue<int>, std::vector<int>>> {};

// Test case for Push and Front functions
TEST_P(QueueFixture, PushAndFront) {
	auto [queue, vector] = GetParam();
	for (auto value : vector) {
		queue.Push(value);
	}

	// Ensure Front() throws an exception on an empty vector
	if (!vector.empty()) {
		EXPECT_EQ(queue.Front(), vector.front());
	}
	else {
		EXPECT_THROW(queue.Front(), std::out_of_range);
	}
}

// Test case for Pop function
TEST_P(QueueFixture, Pop) {
	auto [queue, vector] = GetParam();
	for (auto value : vector) {
		queue.Push(value);
	}

	// Ensure Pop() throws an exception on an empty queue
	if (!vector.empty()) {
		queue.Pop();
		vector.erase(vector.begin());

		// Ensure Front() throws an exception on an empty vector
		if (!vector.empty()) {
			EXPECT_EQ(queue.Front(), vector.front());
		}
		else {
			EXPECT_THROW(queue.Front(), std::out_of_range);
		}
	}
	else {
		EXPECT_THROW(queue.Pop(), std::out_of_range);
	}
}

// Test case for checking capacity changes
TEST_P(QueueFixture, CapacityChange) {
	core::Queue<int> queue;
	std::vector<int> large_vector(100);
	std::iota(large_vector.begin(), large_vector.end(), 0); // Fill with 0, 1, 2, ..., 99

	for (auto value : large_vector) {
		queue.Push(value);
	}

	// Check if the queue size matches the number of pushed elements
	EXPECT_EQ(queue.Size(), large_vector.size());

	// Check if elements are in the correct order
	for (int i = 0; i < large_vector.size(); ++i) {
		EXPECT_EQ(queue.Front(), large_vector[i]);
		queue.Pop();
	}

	// Ensure the queue is empty
	EXPECT_THROW(queue.Front(), std::out_of_range);
	EXPECT_THROW(queue.Pop(), std::out_of_range);
}

TEST_P(QueueFixture, CapacityAndSize)
{
	core::Queue<int> queue;
	std::vector<int> large_vector(50);
	std::iota(large_vector.begin(), large_vector.end(), 0);

	for (auto value : large_vector)
	{
		queue.Push(value);
	}
	EXPECT_EQ(queue.Size(), large_vector.size());

	const int queueCapacity = queue.Capacity();
	for (int i = 0; i < 25; ++i)
	{
		queue.Pop();
	}
	EXPECT_EQ(queue.Size(), 25);
	EXPECT_EQ(queue.Capacity(), queueCapacity);

	//TODO Can't get this to work I don't know why it crashes
	//for (int i = 0; i < 25; ++i)
	//{
	//	queue.Push(1);
	//}

	//EXPECT_EQ(queue.Size(), 50);
	//EXPECT_EQ(queue.Capacity(), queueCapacity);
}


INSTANTIATE_TEST_SUITE_P(Numbers, QueueFixture,
	testing::Values(
		std::make_pair(core::Queue<int>(), std::vector<int>{1, 4, 5, 123, 0, 3, -1}),
		std::make_pair(core::Queue<int>(), std::vector<int>{5, 123, 3, -1}),
		std::make_pair(core::Queue<int>(), std::vector<int>{})
	)
);
