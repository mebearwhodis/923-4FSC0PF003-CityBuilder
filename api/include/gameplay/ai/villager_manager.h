#ifndef API_GAMEPLAY_AI_AI_MANAGER_H_
#define API_GAMEPLAY_AI_AI_MANAGER_H_
#include <SFML/Graphics/Drawable.hpp>

#include "woodsman.h"
#include "graphics/sprite_entity.h"
#include "world_generation/tile.h"
#include "world_generation/tilemap.h"


class VillagerManager : public sf::Drawable
{

	std::vector<Woodsman> woodsman_;


	//TODO Update()/Tick()

public:
	void SpawnVillager(const Tile& tile, Tilemap& tilemap, VillagerType type);
	void Tick();
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif // API_GAMEPLAY_AI_AI_MANAGER_H_
