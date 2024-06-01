#include "graphics/Tilemap.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "graphics/ResourceManager.h"

// Fix 1 : initiate static in the cc file
sf::Vector2u Tilemap::playground_size_u_ = sf::Vector2u(50, 50);
sf::Vector2u Tilemap::playground_tile_size_u_ = sf::Vector2u(64, 64);

void Tilemap::Generate()
{
	int numberOfTiles = 0;
	tiles_.clear();

	for (unsigned int x = 0; x < playground_size_u_.x; x++)
	{
		for (unsigned int y = 0; y < playground_size_u_.y; y++)
		{
			std::cout << "Add a sprite in the\t(" << x << "," << y << ")\t position." << std::endl;

			int idx = x * playground_size_u_.y + y;
			tiles_.emplace_back() = sf::Sprite();
			tiles_[idx].setTexture(ResourceManager::Get().GetTexture(ResourceManager::Resource::TerrainForest));
			tiles_[idx].setPosition(x * playground_tile_size_u_.x, y * playground_tile_size_u_.y);
			numberOfTiles++;
		}
	}
	std::cout << "Total tiles: " << numberOfTiles << std::endl;
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto tile : tiles_)
	{
		target.draw(tile, states);
	}
}
