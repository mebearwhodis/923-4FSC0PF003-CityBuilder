#ifndef API_GAMEPLAY_AI_AI_MANAGER_H_
#define API_GAMEPLAY_AI_AI_MANAGER_H_
#include <SFML/Graphics/Drawable.hpp>

#include "gatherer.h"
#include "miner.h"
#include "woodsman.h"
#include "gameplay/economy_manager.h"
#include "graphics/sprite_entity.h"
#include "world_generation/tile.h"
#include "world_generation/tilemap.h"


class VillagerManager : public sf::Drawable
{

	std::vector<Woodsman> woodsmen_;
	std::vector<Miner> miners_;
	std::vector<Gatherer> gatherers_;

public:
	void SpawnVillager(sf::Vector2f position, Tilemap& tilemap, VillagerType type);
	void ClearVillagers();
	void Tick(EconomyManager& economy_manager);
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif // API_GAMEPLAY_AI_AI_MANAGER_H_
