#include "gameplay/ai/villager_manager.h"

#include "gameplay/ai/woodsman.h"

void VillagerManager::SpawnVillager(sf::Vector2f position, Tilemap& tilemap, VillagerType type)
{
	switch(type)
	{
	case VillagerType::kVillager:
		break;
	case VillagerType::kWoodsman:
		woodsman_.emplace_back(position.x, position.y, 256, tilemap);
		break;
	case VillagerType::kMiner:
		break;
	default: ;
	}
}

void VillagerManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& w : woodsman_)
	{
		target.draw(w, states);
	}
}

void VillagerManager::Tick()
{
	for (auto& w : woodsman_)
	{
		w.Tick();
	}
}
