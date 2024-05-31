#include <maths/vec2f.h>
#include <gtest/gtest.h>


struct Vec2fOperatorFixture :
	public ::testing::TestWithParam<std::pair<core::Vec2f, core::Vec2f>>
{

};

TEST_P(Vec2fOperatorFixture, Add)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 + v2;
	EXPECT_FLOAT_EQ(result.x, v1.x + v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y + v2.y);
}

TEST_P(Vec2fOperatorFixture, Sub)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 - v2;
	EXPECT_FLOAT_EQ(result.x, v1.x - v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y - v2.y);

	const auto neg1 = -v1;
	const auto neg2 = -v2;
	EXPECT_FLOAT_EQ(neg1.x, -v1.x);
	EXPECT_FLOAT_EQ(neg1.y, -v1.y);
	EXPECT_FLOAT_EQ(neg2.x, -v2.x);
	EXPECT_FLOAT_EQ(neg2.y, -v2.y);
}

TEST_P(Vec2fOperatorFixture, Dot)
{
	auto [v1, v2] = GetParam();
	const auto result = core::Vec2f::Dot(v1, v2);
	EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}

//For two vectors to be perpendicular, their dot products must be equal to 0
TEST_P(Vec2fOperatorFixture, Perpendicular)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Perpendicular();
	const auto p2 = v2.Perpendicular();
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v1, p1), 0);
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v2, p2), 0);

	const auto r1 = v1.Perpendicular2();
	const auto r2 = v2.Perpendicular2();
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v1, r1), 0);
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v2, r2), 0);
}

TEST_P(Vec2fOperatorFixture, MultiplyByScalar)
{
	auto [v1, v2] = GetParam();
	const auto result1 = v1 * v2.x;
	const auto result2 = v1.x * v2;
	EXPECT_FLOAT_EQ(result1.x, v1.x * v2.x);
	EXPECT_FLOAT_EQ(result1.y, v1.y * v2.x);
	EXPECT_FLOAT_EQ(result2.x, v1.x * v2.x);
	EXPECT_FLOAT_EQ(result2.y, v1.x * v2.y);
}

TEST_P(Vec2fOperatorFixture, DivideByScalar)
{
	auto [v1, v2] = GetParam();

	if (v2.x != 0)
	{
		const auto result1 = v1 / v2.x;
		EXPECT_FLOAT_EQ(result1.x, v1.x / v2.x);
		EXPECT_FLOAT_EQ(result1.y, v1.y / v2.x);
	}
	else
	{
		//Do nothing
	}

	if (v2.y != 0)
	{
		const auto result2 = v1 / v2.y;
		EXPECT_FLOAT_EQ(result2.x, v1.x / v2.y);
		EXPECT_FLOAT_EQ(result2.y, v1.y / v2.y);
	}
	else
	{
		//Do nothing
	}
}

TEST_P(Vec2fOperatorFixture, VectorLengths)
{
	auto [v1, v2] = GetParam();
	const auto squareLength1 = v1.SquareLength();
	const auto squareLength2 = v2.SquareLength();
	EXPECT_FLOAT_EQ(squareLength1, v1.x * v1.x + v1.y * v1.y);
	EXPECT_FLOAT_EQ(squareLength2, v2.x * v2.x + v2.y * v2.y);

	const auto length1 = v1.Length();
	const auto length2 = v2.Length();
	EXPECT_FLOAT_EQ(length1, v1.Sqrt(squareLength1));
	EXPECT_FLOAT_EQ(length2, v2.Sqrt(squareLength2));
}

TEST_P(Vec2fOperatorFixture, Normalized)
{
	auto [v1, v2] = GetParam();

	const auto normalized1 = v1.Normalized();
	const auto normalized2 = v2.Normalized();

	const auto length1 = normalized1.Length();
	const auto length2 = normalized2.Length();

	//If the vector is not zero, the length of the normalized vector should be 1
	if (v1.x != 0 || v1.y != 0)
	{
		EXPECT_NEAR(length1, 1.0, 1e-6);
	}
	else
	{
		EXPECT_FLOAT_EQ(length1, 0);
	}

	if (v2.x != 0 || v2.y != 0)
	{
		EXPECT_NEAR(length2, 1.0, 1e-6);
	}
	else
	{
		EXPECT_FLOAT_EQ(length2, 0);
	}
}

TEST_P(Vec2fOperatorFixture, LERP)
{
	auto [v1, v2] = GetParam();
	const auto lerp0 = v1.LERP(v2, 0);
	const auto lerp1 = v1.LERP(v2, 1);
	EXPECT_FLOAT_EQ(lerp0.x, v1.x);
	EXPECT_FLOAT_EQ(lerp0.y, v1.y);
	EXPECT_FLOAT_EQ(lerp1.x, v2.x);
	EXPECT_FLOAT_EQ(lerp1.y, v2.y);
}

//Example Vectors
INSTANTIATE_TEST_SUITE_P(AllNumbers, Vec2fOperatorFixture,
	testing::Values(
		std::pair{ core::Vec2f{-4.5f,3.2f}, core::Vec2f{2.1f,4.05f} },
		std::pair{ core::Vec2f{-10.4f,-15.112f}, core::Vec2f{-25.23f,35.7f} },
		std::pair{ core::Vec2f{1.33f,3.99f}, core::Vec2f{2.005f,4.2f} },
		std::pair{ core::Vec2f{10.1f,15.6f}, core::Vec2f{25.662f,35.22134f} },
		std::pair{ core::Vec2f{}, core::Vec2f{} },
		std::pair{ core::Vec2f{1.1f,5.0007f}, core::Vec2f{} },
		std::pair{ core::Vec2f{}, core::Vec2f{1.93f,7.4f} }
	)
);