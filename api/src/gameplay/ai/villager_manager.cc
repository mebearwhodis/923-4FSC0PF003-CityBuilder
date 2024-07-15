#include "gameplay/ai/villager_manager.h"

#include "gameplay/ai/woodsman.h"

void VillagerManager::SpawnVillager(sf::Vector2f position, Tilemap& tilemap, VillagerType type)
{
	switch(type)
	{
	case VillagerType::kVillager:
		break;
	case VillagerType::kWoodsman:
		woodsmen_.emplace_back(Woodsman(position.x, position.y, 64, tilemap));
		break;
	case VillagerType::kMiner:
		miners_.emplace_back(Miner(position.x, position.y, 64, tilemap));
		break;
	case VillagerType::kGatherer:
		gatherers_.emplace_back(Gatherer(position.x, position.y, 64, tilemap));
		break;
	default: ;
	}
}

void VillagerManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& w : woodsmen_)
	{
		target.draw(w, states);
	}
	for (const auto& w : miners_)
	{
		target.draw(w, states);
	}
	for (const auto& w : gatherers_)
	{
		target.draw(w, states);
	}
}

void VillagerManager::Tick()
{
	for (auto& w : woodsmen_)
	{
		w.Tick();
	}
	for (auto& w : miners_)
	{
		w.Tick();
	}
	for (auto& w : gatherers_)
	{
		w.Tick();
	}
}
