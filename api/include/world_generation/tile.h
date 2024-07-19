#ifndef API_WORLD_GENERATION_TILE_H_
#define API_WORLD_GENERATION_TILE_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "graphics/resource_manager.h"

class Tile : public sf::Drawable
{
private:
	sf::Vector2u size_;
	sf::Sprite sprite_;
	sf::Vector2f position_;
	TileType type_;
	bool is_buildable_;
	bool is_walkable_;
	bool selected_;
	int tile_texture_index_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Tile();
	Tile(TileType type, float x, float y, bool walkable, bool buildable);
	Tile(int type, float x, float y, int texture_index, bool walkable, bool buildable);

	void Deselect();
	sf::Vector2f Position() const { return sprite_.getPosition(); }
	void Select();
	void SetColor(const sf::Color& color);

	// Getters and setters
	TileType type() const { return type_; }
	bool is_buildable() const { return is_buildable_; }
	bool is_walkable() const { return is_walkable_; }
	int tile_texture_index() const { return tile_texture_index_; }

	void set_walkable(const bool walkable) { is_walkable_ = walkable; }
	void set_is_buildable(const bool buildable) { is_buildable_ = buildable; }
	void set_type(TileType type);
};

#endif