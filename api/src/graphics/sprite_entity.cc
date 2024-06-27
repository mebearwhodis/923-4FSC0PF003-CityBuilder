#include <SFML/Graphics/RenderTarget.hpp>

#include "graphics/sprite_entity.h"
#include "graphics/resource_manager.h"

SpriteEntity::SpriteEntity(float x, float y)
{
	sprite_.setPosition(x, y);

	//frame_.setPosition(x, y);
	//frame_.setSize(sf::Vector2f(64,64));
	frame_.setFillColor(sf::Color(100, 100, 100, 0));
	frame_.setOutlineColor(sf::Color::Magenta);
	frame_.setOutlineThickness(-1);

}

void SpriteEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
	target.draw(frame_, states);
}