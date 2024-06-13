#ifndef API_GRAPHICS_EDITOR_H_
#define API_GRAPHICS_EDITOR_H_
#include <SFML/Graphics/RectangleShape.hpp>

#include "world_generation/tile.h"

//TODO put in a "gameplay" folder
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
#endif // API_GRAPHICS_EDITOR_H_


//TODO: class Building with enum of BuildingType
//Sprite, BuildingType, Cost, State
//More specific building classes could inherit from it (Building->House/Sawmill/Forge/etc. could inherit and add specific function)