#include <gtest/gtest.h>
#include "containers/vector.h"

TEST(VectorTest, DefaultConstructor)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec;
    EXPECT_EQ(vec.Size(), 0);
}

TEST(VectorTest, PushBack)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, EmplaceBack)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec;
    vec.EmplaceBack(1);
    vec.EmplaceBack(2);
    vec.EmplaceBack(3);
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, PopBack)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    vec.PopBack();
    EXPECT_EQ(vec.Size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, BeginEnd)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec;
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

TEST(VectorTest, OperatorIndex)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, InitializerListConstructor)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec = { 1, 2, 3 };
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, Insert)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec = { 1, 3, 4 };
    vec.Insert(1, 2);
    EXPECT_EQ(vec.Size(), 4);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
}

TEST(VectorTest, Erase)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec = { 1, 2, 3, 4 };
    vec.Erase(1);
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 4);
}

TEST(VectorTest, Reserve)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec;
    vec.Reserve(10);
    EXPECT_EQ(vec.Size(), 0);
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    EXPECT_EQ(vec.Size(), 3);
    vec.PushBack(4);
    EXPECT_EQ(vec.Size(), 4);
}

TEST(VectorTest, EmptyPopBack)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec;
    EXPECT_THROW(vec.PopBack(), std::out_of_range);
}

TEST(VectorTest, EmptyErase)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec;
    EXPECT_THROW(vec.Erase(0), std::out_of_range);
}

TEST(VectorTest, OutOfBoundsIndex)
{
    core::Vector<int, std::allocator<int>, 3, 2> vec;
    vec.PushBack(1);
    ASSERT_DEATH(vec[1], "");
}
