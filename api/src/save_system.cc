#include <iostream>
#include <fstream>

#include "save_system.h"

using json = nlohmann::json;

void SaveSystem::SaveGame(Tilemap& tilemap, BuildingManager& building_manager, EconomyManager& economy_manager, const std::string& file_name)
{
	nlohmann::json json_level;
	json_level["map_size_x"] = tilemap.playground_size_u().x;
	json_level["map_size_y"] = tilemap.playground_size_u().y;
	json_level["tile_size_x"] = tilemap.playground_tile_size_u().x;
	json_level["tile_size_y"] = tilemap.playground_tile_size_u().y;

	json_level["tiles"] = nlohmann::json::array();
	for (const auto& tile : tilemap.tiles())
	{
		nlohmann::json tile_data;
		tile_data["x"] = tile.Position().x;
		tile_data["y"] = tile.Position().y;
		tile_data["type"] = static_cast<int>(tile.type());
		tile_data["texture_index"] = tile.tile_texture_index();
		tile_data["walkable"] = tile.is_walkable();
		tile_data["buildable"] = tile.is_buildable();
		json_level["tiles"].push_back(tile_data);
	}

	json_level["trees"] = nlohmann::json::array();
	for (const auto& tree : tilemap.trees())
	{
		nlohmann::json tree_data;
		tree_data["x"] = tree.x;
		tree_data["y"] = tree.y;
		json_level["trees"].push_back(tree_data);
	}

	json_level["cut_trees"] = nlohmann::json::array();
	for (const auto& cut_tree : tilemap.cut_trees())
	{
		nlohmann::json cut_tree_data;
		cut_tree_data["x"] = cut_tree.x;
		cut_tree_data["y"] = cut_tree.y;
		json_level["cut_trees"].push_back(cut_tree_data);
	}

	json_level["stones"] = nlohmann::json::array();
	for (const auto& stone : tilemap.stones())
	{
		nlohmann::json stone_data;
		stone_data["x"] = stone.x;
		stone_data["y"] = stone.y;
		json_level["stones"].push_back(stone_data);
	}

	json_level["mined_stones"] = nlohmann::json::array();
	for (const auto& mined_stone : tilemap.mined_stones())
	{
		nlohmann::json mined_stone_data;
		mined_stone_data["x"] = mined_stone.x;
		mined_stone_data["y"] = mined_stone.y;
		json_level["mined_stone"].push_back(mined_stone_data);
	}

	json_level["berries"] = nlohmann::json::array();
	for (const auto& berry : tilemap.berries())
	{
		nlohmann::json berry_data;
		berry_data["x"] = berry.x;
		berry_data["y"] = berry.y;
		json_level["berries"].push_back(berry_data);
	}

	json_level["gathered_berries"] = nlohmann::json::array();
	for (const auto& gathered_berry : tilemap.gathered_berries())
	{
		nlohmann::json gathered_berry_data;
		gathered_berry_data["x"] = gathered_berry.x;
		gathered_berry_data["y"] = gathered_berry.y;
		json_level["gathered_berries"].push_back(gathered_berry_data);
	}

	json_level["storages"] = nlohmann::json::array();
	for (const auto& storage : tilemap.storages())
	{
		nlohmann::json storage_data;
		storage_data["x"] = storage.x;
		storage_data["y"] = storage.y;
		json_level["storages"].push_back(storage_data);
	}

	json_level["buildings"] = nlohmann::json::array();
	for (const auto& building : building_manager.buildings())
	{
		nlohmann::json building_data;
		building_data["type"] = static_cast<int>(building.type());
		building_data["x"] = building.Position().x;
		building_data["y"] = building.Position().y;
		json_level["buildings"].push_back(building_data);
	}

	json_level["current_food"] = economy_manager.food();
	json_level["current_wood"] = economy_manager.wood();
	json_level["current_stone"] = economy_manager.stone();
	json_level["current_population"] = economy_manager.current_population();
	json_level["total_population"] = economy_manager.total_population();
	json_level["current_house_cost"] = economy_manager.current_house_cost();
	json_level["current_forge_cost"] = economy_manager.current_forge_cost();
	json_level["current_sawmill_cost"] = economy_manager.current_sawmill_cost();
	json_level["current_storage_cost"] = economy_manager.current_storage_cost();

	std::ofstream file(file_name);
	if (file.is_open()) {
		file << json_level.dump(4);
		file.close();
	}
	else {
		std::cerr << "Failed to open file for writing: " << file_name << std::endl;
	}
}


void SaveSystem::LoadGame(Tilemap& tilemap, BuildingManager& building_manager, EconomyManager& economy_manager, VillagerManager& villager_manager, const std::string& file_name)
{
	tilemap.Clear();
	tilemap.ClearVectors();
	building_manager.ClearBuildings();
	economy_manager.ClearAll();
	villager_manager.ClearVillagers();


	std::ifstream file(file_name);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << file_name << std::endl;
		return;
	}

	try
	{
		nlohmann::json json_level;
		file >> json_level;
		file.close();

		if (json_level.contains("map_size_x") && json_level.contains("map_size_y") &&
			json_level.contains("tile_size_x") && json_level.contains("tile_size_y"))
		{
			tilemap.Setup(sf::Vector2u(json_level["map_size_x"], json_level["map_size_y"]), sf::Vector2u(json_level["tile_size_x"], json_level["tile_size_y"]));
		}
		else
		{
			std::cerr << "Missing or invalid map or tile size." << std::endl;
			return;
		}

		auto tiles_array = json_level["tiles"];
		for (const auto& tile_data : tiles_array)
		{
			int type_int = tile_data["type"];
			float x = tile_data["x"];
			float y = tile_data["y"];
			int texture_index = tile_data["texture_index"];
			bool walkable = tile_data["walkable"];
			bool buildable = tile_data["buildable"];

			if (type_int >= 0 && type_int < static_cast<int>(TileType::kLength))
			{
				tilemap.LoadTile(type_int, x, y, texture_index, walkable, buildable);
			}
		}

		auto trees_array = json_level["trees"];
		for (const auto& tree_data : trees_array)
		{
			float x = tree_data["x"];
			float y = tree_data["y"];
			tilemap.LoadElement(TileType::kForest, x, y);
		}

		auto cut_trees_array = json_level["cut_trees"];
		for (const auto& cut_tree_data : cut_trees_array)
		{
			float x = cut_tree_data["x"];
			float y = cut_tree_data["y"];
			tilemap.LoadElement(TileType::kForestCutDown, x, y);
		}

		auto stones_array = json_level["stones"];
		for (const auto& stone_data : stones_array)
		{
			float x = stone_data["x"];
			float y = stone_data["y"];
			tilemap.LoadElement(TileType::kStone, x, y);
		}

		auto mined_stones_array = json_level["mined_stones"];
		for (const auto& mined_stone_data : mined_stones_array)
		{
			float x = mined_stone_data["x"];
			float y = mined_stone_data["y"];
			tilemap.LoadMinedStone(x, y);
		}

		auto berries_array = json_level["berries"];
		for (const auto& berry_data : berries_array)
		{
			float x = berry_data["x"];
			float y = berry_data["y"];
			tilemap.LoadElement(TileType::kBerryFull, x, y);
		}

		auto gathered_berries_array = json_level["gathered_berries"];
		for (const auto& gathered_berry_data : gathered_berries_array)
		{
			float x = gathered_berry_data["x"];
			float y = gathered_berry_data["y"];
			tilemap.LoadElement(TileType::kBerryEmpty, x, y);
		}

		auto storages_array = json_level["storages"];
		for (const auto& storage_data : storages_array)
		{
			float x = storage_data["x"];
			float y = storage_data["y"];
			tilemap.LoadElement(TileType::kStorage, x, y);
		}

		auto buildings_array = json_level["buildings"];
		for (const auto& building_data : buildings_array)
		{
			int type_int = building_data["type"];
			float x = building_data["x"];
			float y = building_data["y"];

			if (type_int >= 0 && type_int < static_cast<int>(TileType::kLength))
			{
				building_manager.LoadBuilding(type_int, x, y);
				if(type_int == static_cast<int>(TileType::kForge))
				{
					villager_manager.SpawnVillager(sf::Vector2f(x, y), tilemap, VillagerType::kMiner);
				}
				else if(type_int == static_cast<int>(TileType::kSawmill))
				{
					villager_manager.SpawnVillager(sf::Vector2f(x, y), tilemap, VillagerType::kWoodsman);
				}
				else if(type_int == static_cast<int>(TileType::kStorage))
				{
					villager_manager.SpawnVillager(sf::Vector2f(x, y), tilemap, VillagerType::kGatherer);
				}
			}
		}

		auto current_food = json_level["current_food"];
		economy_manager.AddFood(current_food);

		auto current_wood = json_level["current_wood"];
		economy_manager.AddWood(current_wood);

		auto current_stone = json_level["current_stone"];
		economy_manager.AddStone(current_stone);

		auto current_population = json_level["current_population"];
		economy_manager.AddPopulation(current_population);

		auto total_population = json_level["total_population"];
		economy_manager.AddTotalPopulation(total_population);

		auto current_house_cost = json_level["current_house_cost"];
		economy_manager.set_current_house_cost(current_house_cost);

		auto current_forge_cost = json_level["current_forge_cost"];
		economy_manager.set_current_forge_cost(current_forge_cost);

		auto current_sawmill_cost = json_level["current_sawmill_cost"];
		economy_manager.set_current_sawmill_cost(current_sawmill_cost);

		auto current_storage_cost = json_level["current_storage_cost"];
		economy_manager.set_current_storage_cost(current_storage_cost);
	}
	catch (const nlohmann::json::exception& e)
	{
		std::cerr << "Error parsing JSON: " << e.what() << std::endl;
	}
}