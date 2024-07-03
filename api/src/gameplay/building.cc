#include "gameplay/building.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gameplay/building.h"
#include "graphics/resource_manager.h"


Building::Building(float x, float y): SpriteEntity(x, y)
{
	DefineTexture();
}

void Building::DefineTexture()
{
	const auto& textures = ResourceManager::Get().GetTileTextures(TileType::kHouse);
	if (!textures.Size() == 0) {
		const sf::Texture& texture = textures[std::rand() % textures.Size()];
		sprite_.setTexture(texture);
	}
}
