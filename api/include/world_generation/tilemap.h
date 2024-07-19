#ifndef API_WORLD_GENERATION_TILEMAP_H_
#define API_WORLD_GENERATION_TILEMAP_H_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <vector>

#include "tile.h"
#include "graphics/resource_manager.h"
#include "ui/ui_button.h"

class Tilemap : public sf::Drawable
{
private:
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

	void ApplyFadeEffect(const sf::RenderTarget& target);
	void Regrow();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	std::function<void(Tile&)> clicked_tile_;

	void AddToStoragesList(sf::Vector2f position) { storages_.emplace_back(position); }
	bool Gather(sf::Vector2f pos, TileType type);
	void Generate();
	[[nodiscard]] sf::Vector2f GetClosest(sf::Vector2f position, TileType type) const;
	[[nodiscard]] TileType GetSelectedTileType() const;
	std::vector<sf::Vector2f> GetWalkableTiles();
	void HandleEvent(const sf::Event& event, const sf::RenderWindow& window);
	[[nodiscard]] bool IsSelectedTileBuildable() const;
	void Setup(sf::Vector2u playground_size_u, sf::Vector2u playground_tile_size_u);
	void Tick();

	// Methods for saving and loading ------------------------------------------------
	void Clear();
	void ClearVectors();
	void LoadElement(TileType type, float x, float y);
	// Mined stone is not in an enum so it can't be in the LoadElement function
	void LoadMinedStone(float x, float y) { mined_stones_.emplace_back(x, y); }
	void LoadTile(int type, float x, float y, int texture_index, bool walkable, bool buildable);

	//Getters
	[[nodiscard]] sf::Vector2u playground_size_u() const { return playground_size_u_; }
	[[nodiscard]] sf::Vector2u playground_tile_size_u() const { return playground_tile_size_u_; }

	[[nodiscard]] std::vector<Tile> tiles() const { return tiles_; }
	[[nodiscard]] std::vector<sf::Vector2f> trees() const { return trees_; }
	[[nodiscard]] std::vector<sf::Vector2f> cut_trees() const { return cut_trees_; }
	[[nodiscard]] std::vector<sf::Vector2f> stones() const { return stones_; }
	[[nodiscard]] std::vector<sf::Vector2f> mined_stones() const { return mined_stones_; }
	[[nodiscard]] std::vector<sf::Vector2f> berries() const { return berries_; }
	[[nodiscard]] std::vector<sf::Vector2f> gathered_berries() const { return gathered_berries_; }
	[[nodiscard]] std::vector<sf::Vector2f> storages() const { return storages_; }
};
#endif
