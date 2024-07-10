#ifndef API_GRAPHICS_TILEMAP_H_
#define API_GRAPHICS_TILEMAP_H_

#include <functional>
#include <iostream>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include "tile.h"
#include "../graphics/resource_manager.h"
#include "ui/ui_button.h"

class Tilemap : public sf::Drawable {
	sf::Vector2u playground_size_u_;
	sf::Vector2u playground_tile_size_u_;
	std::vector<Tile> tiles_;

	//TODO peut-�tre plut�t faire un vecteur de Tiles de Type arbre?:
	std::vector<sf::Vector2f> trees_;
	Tile* tile_selected_ = nullptr;

	void applyFadeEffect(sf::RenderTarget& target); // New method to apply fade effect

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Setup(sf::Vector2u playground_size_u, sf::Vector2u playground_tile_size_u);
	void Generate();
	void Clear();
	void HandleEvent(const sf::Event& event, const sf::RenderWindow& window);
	[[nodiscard]] bool GatherTree(sf::Vector2f pos);

	std::function<void(Tile&)> clicked_tile_;
	sf::Vector2u playground_size_u() const { return playground_size_u_; }

	std::vector<sf::Vector2f> GetWalkableTiles();

	sf::Vector2f GetClosestTree(sf::Vector2f position);

	// Getter function to retrieve the TileType of the selected tile
	TileType GetSelectedTileType() const;
};

//Tile GetTileAt(sf::Vector2f position, const sf::View& view, const sf::RenderTarget& target) const;
#endif
