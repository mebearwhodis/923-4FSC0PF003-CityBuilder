#include <SFML/Graphics/RenderTarget.hpp>

#include "gameplay/building.h"
#include "graphics/resource_manager.h"

Building::Building(float x, float y)
{
	const auto& textures = ResourceManager::Get().GetTileTextures(TileType::kHouse);
	if (!textures.empty()) {
		const sf::Texture& texture = textures[std::rand() % textures.size()];
		sprite_.setTexture(texture);
	}
	sprite_.setPosition(x, y);
}

void Building::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}