#ifndef API_GAMEPLAY_BUILDING_MANAGER_H_
#define API_GAMEPLAY_BUILDING_MANAGER_H_
#include <SFML/Graphics/RectangleShape.hpp>

#include "../world_generation/tile.h"


class BuildingManager
{
	bool is_active_ = false;
	sf::RectangleShape hover_tile_;

	//std::vector<Building> buildings_;
	//TODO this should inherit from Drawable to draw the buildings?
	//TODO Update()/Tick()

public:
	BuildingManager();
	void ToggleActive();
	sf::RectangleShape HoverTile() { return hover_tile_; }
	void SetHoverTilePosition(sf::Vector2f position);
	bool IsActive() const { return is_active_; }
	void AddBuilding(Tile& tile);

};
#endif // API_GAMEPLAY_BUILDING_MANAGER_H_
