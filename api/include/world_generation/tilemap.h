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
	bool IsSelectedTileBuildable() const;

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

	void LoadElement(TileType type, float x, float y);
	// Mined stone is not in an enum so it can't be in the LoadElement function
	void LoadMinedStone(float x, float y) { mined_stones_.emplace_back(x, y); }

	void clearVectors();
};

//Tile GetTileAt(sf::Vector2f position, const sf::View& view, const sf::RenderTarget& target) const;
#endif
