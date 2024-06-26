#ifndef API_GAMEPLAY_AI_WALKER_H_
#define API_GAMEPLAY_AI_WALKER_H_
#include <chrono>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "../../graphics/sprite_entity.h"

class Walker : public sf::Transformable, public SpriteEntity
{
	// 1: Destination
	// 2: Framerate independant
	// 3: Steering behavior ~ish

private:
	float linear_speed_ = 0;
	sf::Vector2f destination_ = sf::Vector2f(500,500);
	std::chrono::time_point<std::chrono::steady_clock> last_time_;

public:
	Walker(float x, float y, float linear_speed);
	void set_destination(sf::Vector2f destination);
	void set_destination(float x, float y);
	void set_linear_speed(float linear_speed);
	void Tick();
};


#endif // API_GAMEPLAY_AI_WALKER_H_
