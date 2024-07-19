#include "world_generation/tile.h"
#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif
#include "graphics/resource_manager.h"

Tile::Tile(TileType type, float x = 0, float y = 0, bool walkable = true, bool buildable = true)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	selected_ = false;
	type_ = type;

	const auto& textures = ResourceManager::Get().GetTileTextures(type);
	if (!textures.Size() == 0) {
		tile_texture_index_ = std::rand() % textures.Size();
		const sf::Texture& texture = textures[tile_texture_index_];
		sprite_.setTexture(texture);
	}
	sprite_.setPosition(x, y);

	is_walkable_ = walkable;
	is_buildable_ = buildable;
}

Tile::Tile(int type, float x, float y, int texture_index, bool walkable, bool buildable)
{
	selected_ = false;
	type_ = static_cast<TileType>(type);
	const auto& textures = ResourceManager::Get().GetTileTextures(type_);
	if (!textures.Size() == 0) {
		tile_texture_index_ = texture_index;
		const sf::Texture& texture = textures[tile_texture_index_];
		sprite_.setTexture(texture);
	}
	sprite_.setPosition(x, y);

	is_walkable_ = walkable;
	is_buildable_ = buildable;

}

void Tile::set_type(TileType type)
{
	if(type == TileType::kForestCutDown || type == TileType::kForest || type == TileType::kBerryEmpty || type == TileType::kBerryFull || type == TileType::kStone)
	{
		const auto& textures = ResourceManager::Get().GetTileTextures(type);
		const sf::Texture& texture = textures[tile_texture_index_];

		sprite_.setTexture(texture);
	}
	else if(type == TileType::kPlain)
	{
		const auto& textures = ResourceManager::Get().GetTileTextures(type);
		if (!textures.Size() == 0) {
			tile_texture_index_ = std::rand() % textures.Size();
			const sf::Texture& texture = textures[tile_texture_index_];
			sprite_.setTexture(texture);
		}
	}
	type_ = type;
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

