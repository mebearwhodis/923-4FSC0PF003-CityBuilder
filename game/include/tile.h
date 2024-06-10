#ifndef GAME_SRC_TILE_H
#define GAME_SRC_TILE_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

enum class TileType
{
	Plain,
	Forest,
	Ore,
	House
	//...
};

class Tile {

	sf::Vector2u size_;

	sf::Sprite sprite_;
	sf::Texture texture_;

	sf::Vector2f position_;

	TileType type_;
	bool interactable_;


public:
	Tile();

};

#endif