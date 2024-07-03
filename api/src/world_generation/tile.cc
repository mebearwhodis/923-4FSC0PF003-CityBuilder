#include "world_generation/tile.h"
#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif
#include "graphics/resource_manager.h"

Tile::Tile(TileType type, float x = 0, float y = 0, bool walkable = true)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	selected_ = false;
	type_ = type;

	const auto& textures = ResourceManager::Get().GetTileTextures(type);
	if (!textures.Size() == 0) {
		const sf::Texture& texture = textures[std::rand() % textures.Size()];
		sprite_.setTexture(texture);
	}
	sprite_.setPosition(x, y);

	is_walkable_ = walkable;

	outline_.setPosition(x, y);
	outline_.setSize(sf::Vector2f(sprite_.getTexture()->getSize()));
	outline_.setFillColor(sf::Color(100, 100, 100, 0));
	outline_.setOutlineColor(sf::Color::White);
	outline_.setOutlineThickness(-1);
}

void Tile::Select()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	selected_ = true;
}

void Tile::Deselect()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	selected_ = false;
}

void Tile::setColor(const sf::Color& color)
{
	sprite_.setColor(color);
	//outline_.setOutlineColor(color);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

Tile::Tile()
= default;

