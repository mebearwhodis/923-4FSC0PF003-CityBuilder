//#include <maths/vec2i.h>
//#include <gtest/gtest.h>
//
//struct Vec2iOperatorFixture :
//	public ::testing::TestWithParam<std::pair<core::Vec2i, core::Vec2i>>
//{
//
//};
//
//TEST_P(Vec2iOperatorFixture, Add)
//{
//	auto [v1, v2] = GetParam();
//	const auto result = v1 + v2;
//	EXPECT_EQ(result.x, v1.x + v2.x);
//	EXPECT_EQ(result.y, v1.y + v2.y);
//}
//
//TEST_P(Vec2iOperatorFixture, Sub)
//{
//	auto [v1, v2] = GetParam();
//	const auto result = v1 - v2;
//	EXPECT_EQ(result.x, v1.x - v2.x);
//	EXPECT_EQ(result.y, v1.y - v2.y);
//
//	const auto neg1 = -v1;
//	const auto neg2 = -v2;
//	EXPECT_EQ(neg1.x, -v1.x);
//	EXPECT_EQ(neg1.y, -v1.y);
//	EXPECT_EQ(neg2.x, -v2.x);
//	EXPECT_EQ(neg2.y, -v2.y);
//}
//
//TEST_P(Vec2iOperatorFixture, Dot)
//{
//	auto [v1, v2] = GetParam();
//	const auto result = core::Vec2i::Dot(v1, v2);
//	EXPECT_EQ(result, v1.x * v2.x + v1.y * v2.y);
//}
//
////For two vectors to be perpendicular, their dot products must be equal to 0
//TEST_P(Vec2iOperatorFixture, Perpendicular)
//{
//	auto [v1, v2] = GetParam();
//	const auto p1 = v1.Perpendicular();
//	const auto p2 = v2.Perpendicular();
//	EXPECT_EQ(core::Vec2i::Dot(v1, p1), 0);
//	EXPECT_EQ(core::Vec2i::Dot(v2, p2), 0);
//
//	const auto r1 = v1.Perpendicular2();
//	const auto r2 = v2.Perpendicular2();
//	EXPECT_EQ(core::Vec2i::Dot(v1, r1), 0);
//	EXPECT_EQ(core::Vec2i::Dot(v2, r2), 0);
//}
//
//TEST_P(Vec2iOperatorFixture, MultiplyByScalar)
//{
//	auto [v1, v2] = GetParam();
//	const auto result1 = v1 * v2.x;
//	const auto result2 = v1.x * v2;
//	EXPECT_EQ(result1.x, v1.x * v2.x);
//	EXPECT_EQ(result1.y, v1.y * v2.x);
//	EXPECT_EQ(result2.x, v1.x * v2.x);
//	EXPECT_EQ(result2.y, v1.x * v2.y);
//}
//
//TEST_P(Vec2iOperatorFixture, DivideByScalar)
//{
//	auto [v1, v2] = GetParam();
//
//	if (v2.x != 0)
//	{
//		const auto result1 = v1 / v2.x;
//		EXPECT_EQ(result1.x, v1.x / v2.x);
//		EXPECT_EQ(result1.y, v1.y / v2.x);
//	}
//	else
//	{
//		//Do nothing
//	}
//
//	if (v2.y != 0)
//	{
//		const auto result2 = v1 / v2.y;
//		EXPECT_EQ(result2.x, v1.x / v2.y);
//		EXPECT_EQ(result2.y, v1.y / v2.y);
//	}
//	else
//	{
//		//Do nothing
//	}
//}
//
//TEST_P(Vec2iOperatorFixture, VectorLengths)
//{
//	auto [v1, v2] = GetParam();
//	const auto squareLength1 = v1.SquareLength();
//	const auto squareLength2 = v2.SquareLength();
//	EXPECT_EQ(squareLength1, v1.x * v1.x + v1.y * v1.y);
//	EXPECT_EQ(squareLength2, v2.x * v2.x + v2.y * v2.y);
//}
//
////Example Vectors
//INSTANTIATE_TEST_SUITE_P(AllNumbers, Vec2iOperatorFixture,
//	testing::Values(
//		std::pair{ core::Vec2i{-4,3}, core::Vec2i{2,4} },
//		std::pair{ core::Vec2i{-10,-15}, core::Vec2i{-25,35} },
//		std::pair{ core::Vec2i{1,3}, core::Vec2i{2,4} },
//		std::pair{ core::Vec2i{10,15}, core::Vec2i{25,35} },
//		std::pair{ core::Vec2i{}, core::Vec2i{} },
//		std::pair{ core::Vec2i{1,5}, core::Vec2i{} },
//		std::pair{ core::Vec2i{}, core::Vec2i{1,7} }
//	)
//);
//
