#ifndef API_GRAPHICS_TILEMAP_H_
#define API_GRAPHICS_TILEMAP_H_

#include <functional>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include "tile.h"
#include "../graphics/resource_manager.h"
#include "ui/ui_button.h"

class Tilemap : public sf::Drawable {
	sf::Vector2u playground_size_u_;
	sf::Vector2u playground_tile_size_u_;
	std::vector<Tile> tiles_;

	std::vector<sf::Vector2f> trees_;
	std::vector<sf::Vector2f> cut_trees_;
	std::vector<sf::Vector2f> stones_;
	std::vector<sf::Vector2f> mined_stones_;
	std::vector<sf::Vector2f> berries_;
	std::vector<sf::Vector2f> gathered_berries_;
	std::vector<sf::Vector2f> storages_;

	Tile* tile_selected_ = nullptr;

	void applyFadeEffect(sf::RenderTarget& target); // New method to apply fade effect
	void Regrow();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Setup(sf::Vector2u playground_size_u, sf::Vector2u playground_tile_size_u);
	void Generate();
	void Clear();
	void HandleEvent(const sf::Event& event, const sf::RenderWindow& window);
	[[nodiscard]] bool Gather(sf::Vector2f pos, TileType type);

	std::function<void(Tile&)> clicked_tile_;
	sf::Vector2u playground_size_u() const { return playground_size_u_; }
	sf::Vector2u playground_tile_size_u() const { return playground_tile_size_u_; }


	std::vector<sf::Vector2f> GetWalkableTiles();

	sf::Vector2f GetClosest(sf::Vector2f position, TileType type) const;

	// Getter function to retrieve the TileType of the selected tile
	TileType GetSelectedTileType() const;

	void AddToStoragesList(sf::Vector2f position) { storages_.emplace_back(position); }

	void Tick();

	std::vector<Tile> tiles() const { return tiles_; }
	std::vector<sf::Vector2f> trees() const { return trees_; }
	std::vector<sf::Vector2f> cut_trees() const { return cut_trees_; }
	std::vector<sf::Vector2f> stones() const { return stones_; }
	std::vector<sf::Vector2f> mined_stones() const { return mined_stones_; }
	std::vector<sf::Vector2f> berries() const { return berries_; }
	std::vector<sf::Vector2f> gathered_berries() const { return gathered_berries_; }
	std::vector<sf::Vector2f> storages() const { return storages_; }
	void LoadTile(int type, float x, float y, int texture_index, bool walkable, bool buildable);
	void LoadTree(float x, float y) { trees_.emplace_back(x, y); }
	void LoadCutTree(float x, float y) { cut_trees_.emplace_back(x, y); }
	void LoadStone(float x, float y) { stones_.emplace_back(x, y); }
	void LoadMinedStone(float x, float y) { mined_stones_.emplace_back(x, y); }
	void LoadBerry(float x, float y) { berries_.emplace_back(x, y); }
	void LoadGatheredBerry(float x, float y) { gathered_berries_.emplace_back(x, y); }
	void LoadStorage(float x, float y) { storages_.emplace_back(x, y); }

	void clearVectors();
};

//Tile GetTileAt(sf::Vector2f position, const sf::View& view, const sf::RenderTarget& target) const;
#endif

//void SaveSystem::SaveGame(Tilemap& tilemap, BuildingManager& building_manager, EconomyManager& economy_manager, const std::string& file_name)
//{
//	std::cout << "save map 1.1 \n";
//	nlohmann::json json_level;
//	json_level["map_size_x"] = tilemap.playground_size_u().x;
//	json_level["map_size_y"] = tilemap.playground_size_u().y;
//	json_level["tile_size_x"] = tilemap.playground_tile_size_u().x;
//	json_level["tile_size_y"] = tilemap.playground_tile_size_u().y;
//
//	json_level["tiles"] = nlohmann::json::array();
//	for (const auto& tile : tilemap.tiles())
//	{
//		nlohmann::json tile_data;
//		tile_data["x"] = tile.Position().x;
//		tile_data["y"] = tile.Position().y;
//		tile_data["type"] = static_cast<int>(tile.type());
//		tile_data["texture_index"] = tile.tile_texture_index();
//		tile_data["walkable"] = tile.is_walkable();
//		tile_data["buildable"] = tile.is_buildable();
//		json_level["tiles"].push_back(tile_data);
//	}
//
//	json_level["trees"] = nlohmann::json::array();
//	for (const auto& tree : tilemap.trees())
//	{
//		nlohmann::json tree_data;
//		tree_data["x"] = tree.x;
//		tree_data["y"] = tree.y;
//		json_level["trees"].push_back(tree_data);
//	}
//
//	json_level["cut_trees"] = nlohmann::json::array();
//	for (const auto& cut_tree : tilemap.cut_trees())
//	{
//		nlohmann::json cut_tree_data;
//		cut_tree_data["x"] = cut_tree.x;
//		cut_tree_data["y"] = cut_tree.y;
//		json_level["cut_trees"].push_back(cut_tree_data);
//	}
//
//	json_level["stones"] = nlohmann::json::array();
//	for (const auto& stone : tilemap.stones())
//	{
//		nlohmann::json stone_data;
//		stone_data["x"] = stone.x;
//		stone_data["y"] = stone.y;
//		json_level["stones"].push_back(stone_data);
//	}
//
//	json_level["mined_stones"] = nlohmann::json::array();
//	for (const auto& mined_stone : tilemap.mined_stones())
//	{
//		nlohmann::json mined_stone_data;
//		mined_stone_data["x"] = mined_stone.x;
//		mined_stone_data["y"] = mined_stone.y;
//		json_level["mined_stone"].push_back(mined_stone_data);
//	}
//
//	json_level["berries"] = nlohmann::json::array();
//	for (const auto& berry : tilemap.berries())
//	{
//		nlohmann::json berry_data;
//		berry_data["x"] = berry.x;
//		berry_data["y"] = berry.y;
//		json_level["berries"].push_back(berry_data);
//	}
//
//	json_level["gathered_berries"] = nlohmann::json::array();
//	for (const auto& gathered_berry : tilemap.gathered_berries())
//	{
//		nlohmann::json gathered_berry_data;
//		gathered_berry_data["x"] = gathered_berry.x;
//		gathered_berry_data["y"] = gathered_berry.y;
//		json_level["gathered_berries"].push_back(gathered_berry_data);
//	}
//
//	json_level["storages"] = nlohmann::json::array();
//	for (const auto& storage : tilemap.storages())
//	{
//		nlohmann::json storage_data;
//		storage_data["x"] = storage.x;
//		storage_data["y"] = storage.y;
//		json_level["storages"].push_back(storage_data);
//	}
//
//	// Écrire le JSON formaté dans le fichier
//	std::ofstream file(file_name);
//	if (file.is_open()) {
//		file << json_level.dump(4);
//		file.close();
//	}
//	else {
//		std::cerr << "Failed to open file for writing: " << file_name << std::endl;
//	}
//}