#ifndef CORE_MATHS_VEC2F_H_
#define CORE_MATHS_VEC2F_H_

namespace core
{
	/**
	 * \brief Vec2i is a mathematical object represented by two floats
	 */
	struct Vec2f
	{
		float x = 0, y = 0;

		//Addition
		constexpr Vec2f operator+(const Vec2f other) const
		{
			return { x + other.x, y + other.y };
		}

		//Substraction
		constexpr Vec2f operator-(const Vec2f other) const
		{
			return { x - other.x, y - other.y };
		}

		//Opposite
		constexpr Vec2f operator-() const
		{
			return { -x, -y };
		}

		//Dot product
		static constexpr float Dot(const Vec2f v1, const Vec2f v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		//First perpendicular vector
		[[nodiscard]] constexpr Vec2f Perpendicular() const
		{
			return{ -y, x };
		}

		//Second perpendicular vector
		[[nodiscard]] constexpr Vec2f Perpendicular2() const
		{
			return{ y, -x };
		}

		//Multiplication by scalar
		constexpr Vec2f operator*(const float scalar) const
		{
			return { x * scalar, y * scalar };
		}

		//Division by scalar
		constexpr Vec2f operator/(const float scalar) const
		{
			if (scalar == 0) return{ 0,0 };
			return { x / scalar, y / scalar };
		}

		//Vector squarelength
		[[nodiscard]] constexpr float SquareLength() const
		{
			return x * x + y * y;
		}

		//Square root approximation with the Newton-Rahpson method
		static constexpr float Sqrt(const float value)
		{
			if (value <= 0) return 0;
			float x = value;
			float y = (x + 1) / 2;
			while (y < x)
			{
				x = y;
				y = (x + value / x) / 2;
			}
			return x;
		}

		//Vector length
		[[nodiscard]] constexpr float Length() const
		{
			return Sqrt(SquareLength());
		}

		//Normalized vector
		[[nodiscard]] constexpr Vec2f Normalized() const
		{
			float length = Length();
			if (length == 0) return { 0, 0 };
			return { x / length, y / length };
		}

		//LERP(a, b, t) where a & b are Vec2f and t is a float ranging from 0 to 1
		[[nodiscard]] constexpr Vec2f LERP(const Vec2f other, const float t) const
		{
			return { x + t * (other.x - x), y + t * (other.y - y) };
		}

	}; // struct Vec2f

	//Operator overload for multiplication
	constexpr Vec2f operator*(const float scalar, const Vec2f& vec)
	{
		return { scalar * vec.x, scalar * vec.y };
	}

} // namespace core
#endif  // CORE_MATHS_VEC2F_H_