#include "world_generation/tile.h"

#include "graphics/resource_manager.h"

Tile::Tile(ResourceManager::Resource texture, float x = 0, float y = 0, bool walkable = true)
{
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
	selected_ = true;
}

void Tile::Deselect()
{
	selected_ = false;
}


void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
	if(selected_)
	{
		target.draw(outline_, states);
	}
}

Tile::Tile()
= default;

