#ifndef API_GAMEPLAY_BUILDING_MANAGER_H_
#define API_GAMEPLAY_BUILDING_MANAGER_H_

#include <SFML/Graphics/RectangleShape.hpp>

#include "building.h"
#include "world_generation/tile.h"
#include "world_generation/tilemap.h"

class BuildingManager : public sf::Drawable
{
	std::vector<Building> buildings_;
	sf::RectangleShape hover_tile_;
	TileType building_type_ = TileType::kHouse;
	bool is_active_ = false;

	void UpdateHoverTileTexture();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	BuildingManager();

	bool AddBuilding(Tile& tile, Tilemap& tilemap);
	void AddCastle(sf::Vector2f position, const Tilemap& tilemap);
	void ChangeHoverTileColour(sf::Color colour);
	void ClearBuildings() { buildings_.clear(); }
	void LoadBuilding(int type, float x, float y);
	void SetHoverTilePosition(sf::Vector2f position);
	void ToggleActive();

	void set_building_type(TileType building_type);

	bool is_active() const { return is_active_; }
	TileType building_type() const { return building_type_; }
	std::vector<Building> buildings() const { return buildings_; }
	sf::RectangleShape HoverTile() { return hover_tile_; }
};
#endif // API_GAMEPLAY_BUILDING_MANAGER_H_
