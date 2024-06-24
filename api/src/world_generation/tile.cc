#include "world_generation/tile.h"
#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif
#include "graphics/resource_manager.h"

Tile::Tile(ResourceManager::Resource texture, float x = 0, float y = 0, bool walkable = true)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	texture_ = texture;
	sprite_.setTexture(ResourceManager::Get().GetTexture(texture));

	
	sprite_.setPosition(x, y);

	walkable_ = walkable;

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


void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	target.draw(sprite_, states);
	if(selected_)
	{
#ifdef TRACY_ENABLE
		ZoneNamedN(DrawSelected, "Draw Selected Tile", true);
#endif
		target.draw(outline_, states);
	}
}

Tile::Tile()
= default;

