#include "save_system.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

//TODO URGENT save building manager and economy manager
void SaveSystem::SaveGame(Tilemap& tilemap, BuildingManager& building_manager, EconomyManager& economy_manager, const std::string& file_name)
{
	std::cout << "save map 1.1 \n";
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

	// Écrire le JSON formaté dans le fichier
	std::ofstream file(file_name);
	if (file.is_open()) {
		file << json_level.dump(4);
		file.close();
	}
	else {
		std::cerr << "Failed to open file for writing: " << file_name << std::endl;
	}
}

void SaveSystem::LoadGame(Tilemap& tilemap, const std::string& file_name)
{
	// Nettoyer les vecteurs de tuiles et d'arbres existants
	tilemap.Clear();
	tilemap.clearVectors();
	

	// Ouvrir le fichier JSON
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

			//TODO peut-être besoin du reserve jsp
		}
		else
		{
			std::cerr << "Missing or invalid playground dimensions or tile offset in JSON." << std::endl;
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
			tilemap.trees().emplace_back(x, y);
		}

		auto cut_trees_array = json_level["cut_trees"];
		for (const auto& cut_tree_data : cut_trees_array)
		{
			float x = cut_tree_data["x"];
			float y = cut_tree_data["y"];
			tilemap.cut_trees().emplace_back(x, y);
		}

		auto stones_array = json_level["stones"];
		for (const auto& stone_data : stones_array)
		{
			float x = stone_data["x"];
			float y = stone_data["y"];
			tilemap.stones().emplace_back(x, y);
		}

		auto mined_stones_array = json_level["mined_stones"];
		for (const auto& mined_stone_data : mined_stones_array)
		{
			float x = mined_stone_data["x"];
			float y = mined_stone_data["y"];
			tilemap.mined_stones().emplace_back(x, y);
		}

		auto berries_array = json_level["berries"];
		for (const auto& berry_data : berries_array)
		{
			float x = berry_data["x"];
			float y = berry_data["y"];
			tilemap.berries().emplace_back(x, y);
		}

		auto gathered_berries_array = json_level["gathered_berries"];
		for (const auto& gathered_berry_data : gathered_berries_array)
		{
			float x = gathered_berry_data["x"];
			float y = gathered_berry_data["y"];
			tilemap.gathered_berries().emplace_back(x, y);
		}

		auto storages_array = json_level["storages"];
		for (const auto& storage_data : storages_array)
		{
			float x = storage_data["x"];
			float y = storage_data["y"];
			tilemap.storages().emplace_back(x, y);
		}
	}
	catch (const nlohmann::json::exception& e)
	{
		std::cerr << "Error parsing JSON: " << e.what() << std::endl;
	}
}