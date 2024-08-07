#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif

#include "gameplay/building_manager.h"
#include "world_generation/tilemap.h"

void BuildingManager::UpdateHoverTileTexture()
{
	const auto& textures = ResourceManager::Get().GetTileTextures(building_type_);
	if (textures.Size() > 0) {
		const sf::Texture& texture = textures[0];
		hover_tile_.setTexture(&texture);
	}
}

BuildingManager::BuildingManager()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	sf::Vector2f tile_size = sf::Vector2f(64,64);
	sf::RectangleShape hovered_tile;
	hover_tile_.setSize(tile_size);

	hover_tile_.setFillColor(sf::Color(100, 100, 100, 180));
	hover_tile_.setOutlineColor(sf::Color::Magenta);
	hover_tile_.setOutlineThickness(-1);
	hover_tile_.setOrigin(0, 0);
	UpdateHoverTileTexture();
}

void BuildingManager::ToggleActive()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	is_active_ = !is_active_;
}

void BuildingManager::SetHoverTilePosition(const sf::Vector2f position)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	hover_tile_.setPosition(position);
}

bool BuildingManager::AddBuilding(Tile& tile, Tilemap& tilemap)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	if(!is_active_ || !tile.is_buildable() || building_type_ == TileType::kPlain)
	{
		return false;
	}
	else
	{
		tile.set_is_buildable(false);

		buildings_.emplace_back(building_type_, tile.Position().x, tile.Position().y);
		tile.set_type(building_type_);

		if(building_type_ == TileType::kStorage)
		{
			tilemap.AddToStoragesList(tile.Position());
		}

		return true;
	}
}
void BuildingManager::AddCastle(const sf::Vector2f position, const Tilemap& tilemap)
{
	buildings_.emplace_back(TileType::kCastleBase, position.x * tilemap.playground_tile_size_u().x, position.y * tilemap.playground_tile_size_u().y);
	buildings_.emplace_back(TileType::kCastleRoof, position.x * tilemap.playground_tile_size_u().x, (position.y -1) * tilemap.playground_tile_size_u().y);
}

void BuildingManager::LoadBuilding(int type, float x, float y)
{
	buildings_.emplace_back(static_cast<TileType>(type), x, y);
}


void BuildingManager::set_building_type(const TileType building_type)
{
	building_type_ = building_type;
	UpdateHoverTileTexture();
}

void BuildingManager::ChangeHoverTileColour(const sf::Color colour)
{
	hover_tile_.setFillColor(colour);
	hover_tile_.setOutlineColor(colour);
}


void BuildingManager::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& b : buildings_)
	{
		target.draw(b, states);
	}
}
