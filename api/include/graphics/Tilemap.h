#ifndef API_GRAPHICS_TILEMAP_H_
#define API_GRAPHICS_TILEMAP_H_

#include <iostream>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

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


	Tilemap() = default;

private:
	std::vector<sf::Sprite> tiles_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
