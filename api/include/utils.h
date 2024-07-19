#ifndef API_UTILS_H_
#define API_UTILS_H_

#include <cmath>
#include <SFML/System/Vector2.hpp>

	[[nodiscard]] inline float squaredMagnitude(const sf::Vector2f v)
	{
		return  (v.x * v.x + v.y * v.y);
	}

	[[nodiscard]] inline float Magnitude(const sf::Vector2f v)
	{
		return  std::sqrt(squaredMagnitude(v));
	}

	[[nodiscard]] inline sf::Vector2f Normalized(const sf::Vector2f v)
	{
		float norm_x = v.x == 0 ? 0 : v.x / Magnitude(v);
		float norm_y = v.y == 0 ? 0 : v.y / Magnitude(v);
		return{ norm_x, norm_y };
	}


#endif  // API_UTILS_H_