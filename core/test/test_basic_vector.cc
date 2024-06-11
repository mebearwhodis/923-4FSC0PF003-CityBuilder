#include <gtest/gtest.h>
#include "containers/basic_vector.h"

TEST(BasicVectorTest, DefaultConstructor)
{
    core::BasicVector<int, 5> vec;
    EXPECT_EQ(vec.Size(), 0);
}

TEST(BasicVectorTest, PushBack)
{
    core::BasicVector<int, 5> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(BasicVectorTest, PopBack)
{
    core::BasicVector<int, 5> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    vec.PopBack();
    EXPECT_EQ(vec.Size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(BasicVectorTest, BeginEnd)
{
    core::BasicVector<int, 5> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    int sum = 0;
    for (auto it = vec.Begin(); it != vec.End(); ++it)
    {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

TEST(BasicVectorTest, OperatorIndex)
{
    core::BasicVector<int, 5> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(BasicVectorTest, InitializerListConstructor)
{
    core::BasicVector<int, 5> vec = { 1, 2, 3 };
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(BasicVectorTest, Insert)
{
    core::BasicVector<int, 5> vec = { 1, 3, 4 };
    vec.Insert(1, 2);
    EXPECT_EQ(vec.Size(), 4);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
}

TEST(BasicVectorTest, Erase)
{
    core::BasicVector<int, 5> vec = { 1, 2, 3, 4 };
    vec.Erase(1);
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 4);
}

TEST(BasicVectorTest, Reserve)
{
    core::BasicVector<int, 3> vec;
    vec.Reserve(10);
    EXPECT_EQ(vec.Size(), 0);
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    EXPECT_EQ(vec.Size(), 3);
    vec.PushBack(4);
    EXPECT_EQ(vec.Size(), 4);
}

TEST(BasicVectorTest, EmptyPopBack)
{
    core::BasicVector<int, 5> vec;
    EXPECT_THROW(vec.PopBack(), std::out_of_range);
}

TEST(BasicVectorTest, EmptyErase)
{
    core::BasicVector<int, 5> vec;
    EXPECT_THROW(vec.Erase(0), std::out_of_range);
}

TEST(BasicVectorTest, OutOfBoundsIndex)
{
    core::BasicVector<int, 5> vec;
    vec.PushBack(1);
    EXPECT_THROW(vec[1], std::out_of_range);
}

TEST(BasicVectorTest, TransitionStackToHeap)
{
    core::BasicVector<int, 5> vec;

    // Fill the stack storage to capacity
    for (int i = 0; i < 5; ++i)
    {
        vec.PushBack(i);
    }

    EXPECT_FALSE(vec.UsingHeap()); // Ensure it's still using stack storage
    EXPECT_EQ(vec.Size(), 5);

    // Push one more element to trigger transition to heap storage
    vec.PushBack(5);

    EXPECT_TRUE(vec.UsingHeap()); // Now it should be using heap storage
    EXPECT_EQ(vec.Size(), 6);

    // Validate the content
    for (int i = 0; i < 6; ++i)
    {
        EXPECT_EQ(vec[i], i);
    }
}

