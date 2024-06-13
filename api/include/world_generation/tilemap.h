#ifndef API_GRAPHICS_TILEMAP_H_
#define API_GRAPHICS_TILEMAP_H_

#include <functional>
#include <iostream>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include "tile.h"
#include "graphics/resource_manager.h"

class Tilemap : public sf::Drawable
{

public:

	//Initiated in the cc file
	static sf::Vector2u playground_size_u_;
	static sf::Vector2u playground_tile_size_u_;

	Tilemap(sf::Vector2u size)
	{
		tiles_.reserve(size.x * size.y);
	}

	void Generate();
	void Clear();

	void HandleEvent(const sf::Event& event);


	Tilemap() = default;
	//Tile GetTileAt(sf::Vector2f position, const sf::View& view, const sf::RenderTarget& target) const;

	std::function<void(Tile&)> clicked_tile_;

private:
	std::vector<Tile> tiles_;
	Tile* tile_selected_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
