#include "gameplay/building_manager.h"
#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif
#include "world_generation/tilemap.h"

BuildingManager::BuildingManager()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	sf::Vector2f tile_size = sf::Vector2f(64, 64);
	sf::RectangleShape hovered_tile;
	hover_tile_.setSize(tile_size);
	hover_tile_.setFillColor(sf::Color(100, 100, 100, 180));
	hover_tile_.setOutlineColor(sf::Color::Magenta);
	hover_tile_.setOutlineThickness(-1);
	hover_tile_.setOrigin(0, 0);
}

void BuildingManager::ToggleActive()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	is_active_ = !is_active_;
}

void BuildingManager::SetHoverTilePosition(const sf::Vector2f position)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	hover_tile_.setPosition(position);
}


void BuildingManager::AddBuilding(Tile& tile)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	if (!is_active_) { return; }
	if(tile.type() == TileType::kForest)
	{
		std::cout << "Forest" << std::endl;
	}
	if (tile.type() == TileType::kPlain)
	{
		buildings_.emplace_back(tile.Position().x, tile.Position().y);
		//TODO change tiletype, change walkable state, change texture
	}
}

void BuildingManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& b : buildings_)
	{
		target.draw(b, states);
	}
}
