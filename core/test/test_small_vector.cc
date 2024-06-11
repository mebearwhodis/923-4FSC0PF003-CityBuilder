#include <gtest/gtest.h>
#include "containers/small_vector.h"

TEST(SmallVectorTest, DefaultConstructor)
{
    core::SmallVector<int, 5> vec;
    EXPECT_EQ(vec.Size(), 0);
}

TEST(SmallVectorTest, PushBack)
{
    core::SmallVector<int, 5> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(SmallVectorTest, PopBack)
{
    core::SmallVector<int, 5> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    vec.PopBack();
    EXPECT_EQ(vec.Size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(SmallVectorTest, BeginEnd)
{
    core::SmallVector<int, 5> vec;
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

TEST(SmallVectorTest, OperatorIndex)
{
    core::SmallVector<int, 5> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(SmallVectorTest, InitializerListConstructor)
{
    core::SmallVector<int, 5> vec = { 1, 2, 3 };
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(SmallVectorTest, Insert)
{
    core::SmallVector<int, 5> vec = { 1, 3, 4 };
    vec.Insert(1, 2);
    EXPECT_EQ(vec.Size(), 4);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
}

TEST(SmallVectorTest, Erase)
{
    core::SmallVector<int, 5> vec = { 1, 2, 3, 4 };
    vec.Erase(1);
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 4);
}

TEST(SmallVectorTest, Capacity)
{
    core::SmallVector<int, 3> vec;
    EXPECT_EQ(vec.Size(), 0);
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_THROW(vec.PushBack(4), std::overflow_error);
}

TEST(SmallVectorTest, EmptyPopBack)
{
    core::SmallVector<int, 5> vec;
    EXPECT_THROW(vec.PopBack(), std::out_of_range);
}

TEST(SmallVectorTest, EmptyErase)
{
    core::SmallVector<int, 5> vec;
    EXPECT_THROW(vec.Erase(0), std::out_of_range);
}

TEST(SmallVectorTest, OutOfBoundsIndex)
{
    core::SmallVector<int, 5> vec;
    vec.PushBack(1);
    EXPECT_THROW(vec[1], std::out_of_range);
}