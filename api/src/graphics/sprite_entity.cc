#include <SFML/Graphics/RenderTarget.hpp>

#include "graphics/sprite_entity.h"
#include "graphics/resource_manager.h"

SpriteEntity::SpriteEntity(float x, float y)
{
	sprite_.setPosition(x, y);
}

void SpriteEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}