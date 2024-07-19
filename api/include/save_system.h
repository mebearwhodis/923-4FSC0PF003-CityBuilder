#ifndef API_SAVE_SYSTEM_H_
#define API_SAVE_SYSTEM_H_

#include <string>
#include <nlohmann/json.hpp>

#include "gameplay/building_manager.h"
#include "gameplay/economy_manager.h"
#include "gameplay/ai/villager_manager.h"
#include "world_generation/tilemap.h"

class SaveSystem
{
public:
	static void SaveGame(Tilemap& tilemap, BuildingManager& building_manager, EconomyManager& economy_manager, const std::string& file_name);
	static void LoadGame(Tilemap& tilemap, BuildingManager& building_manager, EconomyManager& economy_manager, VillagerManager& villager_manager, const std::string& file_name);
};


#endif // API_SAVE_SYSTEM_H_
