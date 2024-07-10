#include "gameplay/ai/villager_manager.h"

#include "gameplay/ai/woodsman.h"

void VillagerManager::SpawnVillager(const Tile& tile, Tilemap& tilemap, VillagerType type)
{
	switch(type)
	{
	case VillagerType::kVillager:
		break;
	case VillagerType::kWoodsman:
		woodsman_.emplace_back(tile.Position().x, tile.Position().y, 64, tilemap);
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
