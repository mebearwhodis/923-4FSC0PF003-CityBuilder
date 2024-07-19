#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#include <Tracy/TracyC.h>
#endif

#include <random>
#include <SFML/Graphics/RenderTarget.hpp>

#include "maths/perlin_noise.h"
#include "utils.h"
#include "world_generation/tilemap.h"

void Tilemap::Setup(const sf::Vector2u playground_size_u, const sf::Vector2u playground_tile_size_u)
{
	playground_size_u_ = playground_size_u;
	playground_tile_size_u_ = playground_tile_size_u;
}

void Tilemap::Generate()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	int number_of_tiles = 0;
	tiles_.clear();
	tiles_.erase(tiles_.begin(), tiles_.end());
	tiles_.reserve(playground_size_u_.x * playground_size_u_.y);

	// Seed and Perlin noise generators
	const siv::PerlinNoise::seed_type seed = 79425465;
	const siv::PerlinNoise perlin(seed);

	// Different frequencies for different types of clusters
	const double stone_frequency = 0.2; // Medium clusters
	const double tree_frequency = 0.3;  // Small clusters
	const double berry_frequency = 0.5; // Sparse distribution

	// Thresholds to determine the type of tile based on noise values
	const double stone_threshold = 0.5;
	const double tree_threshold = 0.2;
	const double berry_threshold = 0.4;

	for (unsigned int x = 0; x < playground_size_u_.x; x++)
	{
		for (unsigned int y = 0; y < playground_size_u_.y; y++)
		{
			double tile_x = x * playground_tile_size_u_.x;
			double tile_y = y * playground_tile_size_u_.y;

			// Make sure centre of the map is all plains
			if (x == playground_size_u_.x / 2 && (y == playground_size_u_.y / 2 || y == playground_size_u_.y / 2 - 1))
			{
				tiles_.emplace_back(TileType::kPlain, tile_x, tile_y, false, false);
			}
			else if (x > playground_size_u_.x / 2 - 3 && x < playground_size_u_.x / 2 + 3 && y > playground_size_u_.y / 2 - 3 && y < playground_size_u_.y / 2 + 3)
			{
				tiles_.emplace_back(TileType::kPlain, tile_x, tile_y, true, true);
			}
			
			else
			{
				// Generate different noise values for different frequencies
				const double stone_noise = perlin.noise2D(x * stone_frequency, y * stone_frequency);
				const double tree_noise = perlin.noise2D(x * tree_frequency, y * tree_frequency);
				const double berry_noise = perlin.noise2D(x * berry_frequency, y * berry_frequency);

				// Determine tile type based on noise values and thresholds

				if (stone_noise > stone_threshold)
				{
					tiles_.emplace_back(TileType::kStone, tile_x, tile_y, false, false);
					stones_.emplace_back(tile_x, tile_y);
				}
				else if (tree_noise > tree_threshold)
				{
					tiles_.emplace_back(TileType::kForest, tile_x, tile_y, false, false);
					trees_.emplace_back(tile_x, tile_y);
				}
				else
				{
					if (berry_noise > berry_threshold)
					{
						tiles_.emplace_back(TileType::kBerryFull, tile_x, tile_y, true, false);
						berries_.emplace_back(tile_x, tile_y);
					}
					else
					{
						tiles_.emplace_back(TileType::kPlain, tile_x, tile_y, true, true);
					}
				}
			}
			number_of_tiles++;
		}
	}
	tile_selected_ = &(*tiles_.begin());
	tile_selected_->Deselect();
}

void Tilemap::Clear()
{
	tiles_.clear();
}

void Tilemap::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	const sf::Vector2f world_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	// Snap mouse position to the grid
	sf::Vector2f mouse_position(
		static_cast<int>(world_pos.x / playground_tile_size_u_.x) * playground_tile_size_u_.x,
		static_cast<int>(world_pos.y / playground_tile_size_u_.y) * playground_tile_size_u_.y
	);


	const auto tile_found = std::find_if(tiles_.begin(), tiles_.end(), [&mouse_position](Tile& t) {return t.Position() == mouse_position; });

	if (tile_found != tiles_.end())
	{
		tile_selected_ = &(*tile_found);
		tile_selected_->Select();
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		// Check if the left mouse button is pressed
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (clicked_tile_ && tile_selected_) {
				clicked_tile_(*tile_selected_);
			}
			else
			{
				//std::cout << "No callback defined." << std::endl;
				return;
			}
		}
	}
}

bool Tilemap::Gather(sf::Vector2f pos, const TileType type)
{
	std::vector<sf::Vector2f>* type_map = nullptr;
	std::vector<sf::Vector2f>* gathered_map = nullptr;
	TileType new_tile = {};

	switch (type) {
	case TileType::kForest:
		type_map = &trees_;
		gathered_map = &cut_trees_;
		new_tile = TileType::kForestCutDown;
		break;
	case TileType::kStone:
		type_map = &stones_;
		gathered_map = &mined_stones_;
		new_tile = TileType::kPlain;
		break;
	case TileType::kBerryFull:
		type_map = &berries_;
		gathered_map = &gathered_berries_;
		new_tile = TileType::kBerryEmpty;
		break;
	default:;
	}

	if (type_map != nullptr)
	{
		const auto item = std::find_if(type_map->begin(), type_map->end(), [pos](const sf::Vector2f& t) { return pos == t; });
		if (item != type_map->end())
		{
			gathered_map->emplace_back(pos);
			type_map->erase(item);
			const auto tile = std::find_if(tiles_.begin(), tiles_.end(), [pos](const Tile& t) {return pos == t.Position(); });
			if (tile != tiles_.end())
			{
				tile->set_type(new_tile);
				tile->set_walkable(true);
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void Tilemap::Regrow()
{
	std::vector<sf::Vector2f>* type_map = nullptr;
	std::vector<sf::Vector2f>* gathered_map = nullptr;

	TileType new_tile = {};

	const int rnd = rand() % 3;

	switch (rnd) {
	case 0:
		type_map = &trees_;
		gathered_map = &cut_trees_;
		new_tile = TileType::kForest;
		break;
	case 1:
		type_map = &stones_;
		gathered_map = &mined_stones_;
		new_tile = TileType::kStone;
		break;
	case 2:
		type_map = &berries_;
		gathered_map = &gathered_berries_;
		new_tile = TileType::kBerryFull;
		break;
	default:;
	}

	if (gathered_map != nullptr && !gathered_map->empty())
	{
		const int random = rand() % gathered_map->size();
		auto& item = gathered_map->at(random);

		type_map->emplace_back(item.x, item.y);
		
		// Find the iterator for the item and erase it
		const auto it = std::find(gathered_map->begin(), gathered_map->end(), item);
		if (it != gathered_map->end()) {
			gathered_map->erase(it);
		}

		const auto tile = std::find_if(tiles_.begin(), tiles_.end(), [item](const Tile& t) {return sf::Vector2f(item.x, item.y) == t.Position(); });
		if (tile != tiles_.end())
		{
			tile->set_type(new_tile);
			if (new_tile == TileType::kBerryFull)
			{
				tile->set_walkable(true);
			}
			else
			{
				tile->set_walkable(false);
			}
		}
	}
}

std::vector<sf::Vector2f> Tilemap::GetWalkableTiles()
{
	std::vector<sf::Vector2f> walkable_positions;

	std::for_each(tiles_.begin(), tiles_.end(), [&walkable_positions](const Tile& t)
		{
			if (t.is_walkable())
			{
				walkable_positions.emplace_back(t.Position());
			}
		});
	return walkable_positions;
}

sf::Vector2f Tilemap::GetClosest(sf::Vector2f position, const TileType type) const
{
	sf::Vector2f closest;
	float closest_distance = std::numeric_limits<float>::infinity();

	std::vector<sf::Vector2f> type_map;

	switch (type) {
	case TileType::kForest:
		type_map = trees_;
		break;
	case TileType::kStone:
		type_map = stones_;
		break;
	case TileType::kBerryFull:
		type_map = berries_;
		break;
	case TileType::kStorage:
		type_map = storages_;
		break;
	default:;
	}

	std::for_each(type_map.begin(), type_map.end(), [&closest_distance, &closest, position](const sf::Vector2f tree)
		{
			const float squared_distance = squaredMagnitude(tree - position);

			if (squared_distance < closest_distance)
			{
				closest = tree;
				closest_distance = squared_distance;
			}
		});

	return closest;
}

TileType Tilemap::GetSelectedTileType() const {
	if (tile_selected_) {
		return tile_selected_->type();
	}
	else {
		return TileType::kPlain;
	}
}

bool Tilemap::IsSelectedTileBuildable() const {
	if (tile_selected_) {
		return tile_selected_->is_buildable();
	}
	else {
		return false;
	}
}

void Tilemap::Tick()
{
	const int random = rand() % 2000;
	if(random <= 5)
	{
		Regrow();
	}
}

void Tilemap::LoadTile(int type, float x, float y, int texture_index, bool walkable, bool buildable)
{
	if (type >= static_cast<int>(TileType::kHouse))
	{
		tiles_.emplace_back(static_cast<int>(TileType::kPlain), x, y, texture_index, walkable, buildable);
	}
	else
	{
		tiles_.emplace_back(type, x, y, texture_index, walkable, buildable);
	}
}

void Tilemap::LoadElement(const TileType type, float x, float y)
{
	switch (type)
	{
	case TileType::kForest:
		trees_.emplace_back(x, y);
		break;
	case TileType::kForestCutDown:
		cut_trees_.emplace_back(x, y);
		break;
	case TileType::kStone:
		stones_.emplace_back(x, y);
		break;
	case TileType::kBerryFull:
		berries_.emplace_back(x, y);
		break;
	case TileType::kBerryEmpty:
		gathered_berries_.emplace_back(x, y);
		break;
	case TileType::kStorage:
		storages_.emplace_back(x, y);
		break;
	default:;
	}
}

void Tilemap::ClearVectors()
{
	trees_.clear();
	cut_trees_.clear();
	stones_.clear();
	mined_stones_.clear();
	berries_.clear();
	gathered_berries_.clear();
	storages_.clear();
}

void Tilemap::ApplyFadeEffect(const sf::RenderTarget& target)
{
	const sf::View view = target.getView();
	const sf::Vector2f view_center = view.getCenter();
	const sf::FloatRect view_bounds(
		view_center - view.getSize() / 2.f,
		view.getSize()
	);

	const float max_distance = std::max(view_bounds.width, view_bounds.height) / 2.f;

	for (auto& tile : tiles_)
	{
		sf::FloatRect tile_bounds(
			tile.Position().x,
			tile.Position().y,
			static_cast<float>(playground_tile_size_u_.x),
			static_cast<float>(playground_tile_size_u_.y)
		);

		if (view_bounds.intersects(tile_bounds))
		{
			const float distance = std::hypot(tile.Position().x - view_center.x, tile.Position().y - view_center.y);
			const float fade_factor = std::clamp(1.0f - (distance / max_distance), 0.0f, 1.0f);
			sf::Color color = sf::Color(255 * fade_factor, 255 * fade_factor, 255 * fade_factor);
			tile.SetColor(color);
		}
	}
}

void Tilemap::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	//const_cast<Tilemap*>(this)->applyFadeEffect(target);

	for (const auto& tile : tiles_)
	{
		target.draw(tile, states);
	}
}
