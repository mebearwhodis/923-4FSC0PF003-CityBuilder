#include <SFML/Graphics/RenderTarget.hpp>

#include "gameplay/building.h"
#include "graphics/resource_manager.h"

Building::Building(float x, float y)
{
	sprite_.setTexture(ResourceManager::Get().GetTexture(Resource::kHouse));
	sprite_.setPosition(x, y);
}

void Building::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}