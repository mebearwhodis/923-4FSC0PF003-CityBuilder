#ifndef CORE_MATHS_VEC2I_H_
#define CORE_MATHS_VEC2I_H_

namespace core
{
	/**
	 * \brief Vec2i is a mathematical object represented by two integers
	 */
	struct Vec2i
	{
		int x = 0, y = 0;

		//Addition
		constexpr Vec2i operator+(Vec2i other) const
		{
			return { x + other.x, y + other.y };
		}

		//Substraction
		constexpr Vec2i operator-(Vec2i other) const
		{
			return { x - other.x, y - other.y };
		}

		//Opposite
		constexpr Vec2i operator-() const
		{
			return { -x, -y };
		}

		//Dot product
		static constexpr int Dot(Vec2i v1, Vec2i v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		//First perpendicular vector
		constexpr Vec2i Perpendicular() const
		{
			return{ -y, x };
		}

		//Second perpendicular vector
		constexpr Vec2i Perpendicular2() const
		{
			return{ y, -x };
		}

		//Multiplication by scalar
		constexpr Vec2i operator*(int scalar) const
		{
			return{ x * scalar, y * scalar };
		}

		//Division by scalar
		constexpr Vec2i operator/(int scalar) const
		{
			if (scalar == 0) return { 0,0 };
			return { x / scalar, y / scalar };
		}

		//Vector squarelength
		constexpr int SquareLength() const
		{
			return x * x + y * y;
		}

	}; // struct Vec2i

	//Operator overload for multiplication
	constexpr Vec2i operator*(int scalar, const Vec2i& vec)
	{
		return { scalar * vec.x, scalar * vec.y };
	}

} // namespace core
#endif  // CORE_MATHS_VEC2I_H_