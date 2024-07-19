#ifndef API_GAMEPLAY_AI_VILLAGER_MANAGER_H_
#define API_GAMEPLAY_AI_VILLAGER_MANAGER_H_

#include <SFML/Graphics/Drawable.hpp>

#include "gameplay/economy_manager.h"
#include "gatherer.h"
#include "graphics/sprite_entity.h"
#include "miner.h"
#include "woodsman.h"
#include "world_generation/tile.h"
#include "world_generation/tilemap.h"


class VillagerManager : public sf::Drawable
{
private:
	std::vector<Gatherer> gatherers_;
	std::vector<Miner> miners_;
	std::vector<Woodsman> woodsmen_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void SpawnVillager(sf::Vector2f position, Tilemap& tilemap, VillagerType type);
	void ClearVillagers();
	void Tick(EconomyManager& economy_manager);
};
#endif // API_GAMEPLAY_AI_VILLAGER_MANAGER_H_
