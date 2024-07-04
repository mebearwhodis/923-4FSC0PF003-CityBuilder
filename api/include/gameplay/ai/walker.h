#ifndef API_GAMEPLAY_AI_WALKER_H_
#define API_GAMEPLAY_AI_WALKER_H_
#include <chrono>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "../../graphics/sprite_entity.h"
#include "../../pathfinding/path.h"

class Walker : public sf::Transformable, public SpriteEntity
{
	// 1: Destination
	// 2: Framerate independant
	// 3: Steering behavior ~ish

private:
	float linear_speed_ = 0;
	sf::Vector2f destination_;
	std::chrono::time_point<std::chrono::steady_clock> last_time_;
	Path path_;

public:
	Walker(float x, float y, float linear_speed);
	void set_destination(sf::Vector2f destination);
	void set_destination(float x, float y);
	void set_linear_speed(float linear_speed);
	void set_path(const Path& path);
	void Tick();
	sf::Vector2f GetLastDestination() const;
};


#endif // API_GAMEPLAY_AI_WALKER_H_
