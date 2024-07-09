#ifndef API_WORLD_GENERATION_TILE_H_
#define API_WORLD_GENERATION_TILE_H_
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../graphics/resource_manager.h"


class Tile : public sf::Drawable {

	sf::Vector2u size_;
	sf::Sprite sprite_;
	sf::RectangleShape outline_;
	sf::Vector2f position_;
	TileType type_;
	bool is_buildable_;
	bool is_walkable_;
	bool selected_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Tile();
	Tile(TileType type, float x, float y, bool walkable);
	bool is_walkable() const { return is_walkable_; }
	bool is_buildable() const { return is_buildable_; }
	void set_walkable(bool walkable) { is_walkable_ = walkable; }
	void set_is_buildable(bool buildable) { is_buildable_ = buildable; }
	void set_type(TileType type) { type_ = type; }
	sf::Vector2f Position() const { return sprite_.getPosition(); }

	void Select();
	void Deselect();
	void setColor(const sf::Color& color); // New method to set the color
	TileType type() { return type_; }
};

#endif