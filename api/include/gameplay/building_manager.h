#ifndef API_GAMEPLAY_BUILDING_MANAGER_H_
#define API_GAMEPLAY_BUILDING_MANAGER_H_
#include <SFML/Graphics/RectangleShape.hpp>

#include "building.h"
#include "../world_generation/tile.h"
#include "world_generation/tilemap.h"


class BuildingManager : public sf::Drawable
{
	bool is_active_ = false;
	sf::RectangleShape hover_tile_;

	std::vector<Building> buildings_;
	TileType building_type_ = TileType::kHouse;

	void UpdateHoverTileTexture();


public:
	BuildingManager();
	void ToggleActive();
	sf::RectangleShape HoverTile() { return hover_tile_; }
	void SetHoverTilePosition(sf::Vector2f position);
	bool IsActive() const { return is_active_; }
	bool AddBuilding(Tile& tile, Tilemap& tilemap);
	void AddCastle(sf::Vector2f position, const Tilemap& tilemap);
	void LoadBuilding(int type, float x, float y);
	void ClearBuildings() { buildings_.clear(); }
	TileType building_type() const { return building_type_; }
	void set_building_type(TileType building_type);
	void ChangeHoverTileColour(sf::Color colour);
	std::vector<Building> buildings() const { return buildings_; }

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif // API_GAMEPLAY_BUILDING_MANAGER_H_
