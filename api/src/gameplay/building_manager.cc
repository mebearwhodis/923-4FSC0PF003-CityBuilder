#include "gameplay/building_manager.h"

#include "world_generation/tilemap.h"

BuildingManager::BuildingManager()
{
	sf::Vector2f tile_size = sf::Vector2f(Tilemap::playground_tile_size_u_.x, Tilemap::playground_tile_size_u_.y);
	sf::RectangleShape hovered_tile;
	hover_tile_.setSize(tile_size);
	hover_tile_.setFillColor(sf::Color(100, 100, 100, 180));
	hover_tile_.setOutlineColor(sf::Color::Magenta);
	hover_tile_.setOutlineThickness(-1);
	hover_tile_.setOrigin(0, 0);
}

void BuildingManager::ToggleActive()
{
	is_active_ = !is_active_;
}

void BuildingManager::SetHoverTilePosition(const sf::Vector2f position)
{
	hover_tile_.setPosition(position);
}

void BuildingManager::AddBuilding(Tile& tile)
{
	if (!is_active_) { return; }
	std::cout << "Tile clicked:\t" << tile.Position().x << "/" << tile.Position().y << "\t" << std::endl;
	//TODO Add if tiletype... to prevent putting buildings on some types
}
