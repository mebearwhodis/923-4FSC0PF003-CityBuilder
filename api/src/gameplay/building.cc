#include "gameplay/building.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gameplay/building.h"
#include "graphics/resource_manager.h"


Building::Building(TileType type, float x, float y): SpriteEntity(x, y)
{
	type_ = type;
	DefineTexture(static_cast<int>(type));
}

void Building::DefineTexture(int type)
{
	const auto& textures = ResourceManager::Get().GetTileTextures(static_cast<TileType>(type));
	if (textures.Size() > 0) {
		const sf::Texture& texture = textures[std::rand() % textures.Size()];
		sprite_.setTexture(texture);
	}
}


