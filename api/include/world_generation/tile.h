#ifndef API_WORLD_GENERATION_TILE_H_
#define API_WORLD_GENERATION_TILE_H_
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../graphics/resource_manager.h"


class Tile : public sf::Drawable {

	sf::Vector2u size_;
	sf::Sprite sprite_;
	Resource texture_;
	sf::RectangleShape outline_;
	sf::Vector2f position_;
	TileType type_;
	//bool interactible_;
	bool walkable_;
	bool selected_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	//TODO link resources in resource manager to TileType. 
	Tile();
	Tile(Resource texture, float x, float y, bool walkable);
	bool Walkable() const { return walkable_; }
	sf::Vector2f Position() const { return sprite_.getPosition(); }

	void Select();
	void Deselect();
	void setColor(const sf::Color& color); // New method to set the color
};

#endif