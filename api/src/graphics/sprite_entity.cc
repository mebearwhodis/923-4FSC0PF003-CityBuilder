#include <SFML/Graphics/RenderTarget.hpp>

#include "graphics/sprite_entity.h"

SpriteEntity::SpriteEntity(const float x, const float y)
{
	sprite_.setPosition(x, y);

	frame_.setFillColor(sf::Color(100, 100, 100, 0));
	frame_.setOutlineColor(sf::Color::Magenta);
	frame_.setOutlineThickness(-1);
}

void SpriteEntity::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(sprite_, states);
	//target.draw(frame_, states);
}