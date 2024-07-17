#include "gameplay/ai/villager_manager.h"
#include "gameplay/ai/woodsman.h"

void VillagerManager::SpawnVillager(sf::Vector2f position, Tilemap& tilemap, VillagerType type)
{
	switch(type)
	{
	case VillagerType::kVillager:
		break;
	case VillagerType::kWoodsman:
		woodsmen_.emplace_back(position.x, position.y, 64, tilemap);
		break;
	case VillagerType::kMiner:
		miners_.emplace_back(position.x, position.y, 64, tilemap);
		break;
	case VillagerType::kGatherer:
		gatherers_.emplace_back(position.x, position.y, 64, tilemap);
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
	for (const auto& m : miners_)
	{
		target.draw(m, states);
	}
	for (const auto& g : gatherers_)
	{
		target.draw(g, states);
	}
}

void VillagerManager::Tick(EconomyManager& economy_manager)
{
	for (auto& w : woodsmen_)
	{
		w.Tick();
		if(w.can_deposit())
		{
			economy_manager.AddWood(w.resources_held());
			w.ResetResourcesHeld();
			economy_manager.set_text_to_update(true);
		}
	}
	for (auto& m : miners_)
	{
		m.Tick();
		if (m.can_deposit())
		{
			economy_manager.AddStone(m.resources_held());
			m.ResetResourcesHeld();
			economy_manager.set_text_to_update(true);
		}
	}
	for (auto& g : gatherers_)
	{
		g.Tick();
		if (g.can_deposit())
		{
			economy_manager.AddFood(g.resources_held());
			g.ResetResourcesHeld();
			economy_manager.set_text_to_update(true);
		}
	}
}
