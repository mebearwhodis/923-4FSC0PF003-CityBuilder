#ifndef API_UTILS_H_
#define API_UTILS_H_

#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <chrono>


	[[nodiscard]] inline float squaredMagnitude(sf::Vector2f v)
	{
		return  (v.x * v.x + v.y * v.y);
	}


	[[nodiscard]] inline float Magnitude(sf::Vector2f v)
	{
		return  std::sqrt(squaredMagnitude(v));
	}



	[[nodiscard]] inline sf::Vector2f Normalized(sf::Vector2f v)
	{
		float norm_x = v.x == 0 ? 0 : v.x / Magnitude(v);
		float norm_y = v.y == 0 ? 0 : v.y / Magnitude(v);
		return{ norm_x, norm_y };
	}


#endif  // API_UTILS_H_