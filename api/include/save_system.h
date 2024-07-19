#ifndef API_SAVE_SYSTEM_H
#define API_SAVE_SYSTEM_H
#include <string>

#include "gameplay/building_manager.h"
#include "gameplay/economy_manager.h"
#include "gameplay/ai/villager_manager.h"
#include "world_generation/tilemap.h"
#include <nlohmann/json.hpp>


//TODO: SOON Save & Load system
//Things that need saving: me
//Tilemap -> tiles_(type(if type kPlain, then buildable = true), position, walkable, tile_texture_index_)
//all vectors in tilemap
class SaveSystem
{
public:
	static void SaveGame(Tilemap& tilemap, BuildingManager& building_manager, EconomyManager& economy_manager, const std::string& file_name);
	static void LoadGame(Tilemap& tilemap, BuildingManager& building_manager, EconomyManager& economy_manager, VillagerManager& villager_manager, const std::string& file_name);
};







#endif // API_SAVE_SYSTEM_H
