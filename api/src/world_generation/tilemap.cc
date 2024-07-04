#include "world_generation/tilemap.h"

#include <random>
#include <SFML/Graphics/RenderTarget.hpp>
#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#include <Tracy/TracyC.h>
#endif


void Tilemap::Setup(sf::Vector2u playground_size_u, sf::Vector2u playground_tile_size_u)
{
	playground_size_u_ = playground_size_u;
	playground_tile_size_u_ = playground_tile_size_u;
}

void Tilemap::Generate()
{
	//TODO check way to do this with vertex array (or at least check what vertex arrays are)
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	int numberOfTiles = 0;
	tiles_.clear();
	tiles_.erase(tiles_.begin(), tiles_.end());
	tiles_.reserve(playground_size_u_.x * playground_size_u_.y);

	//For now, just simple random
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(1, 10);

	for (unsigned int x = 0; x < playground_size_u_.x; x++)
	{
		for (unsigned int y = 0; y < playground_size_u_.y; y++)
		{


			int idx = x * playground_size_u_.y + y;

			//TODO Perlin Noise/ WFC/ Whatevs


			int rnd = uniform_dist(e1);

			if (rnd <= 3)
			{
				tiles_.emplace_back(TileType::kForest, x * playground_tile_size_u_.x, y * playground_tile_size_u_.y, false);
			}
			if (rnd > 3)
			{
				tiles_.emplace_back(TileType::kPlain, x * playground_tile_size_u_.x, y * playground_tile_size_u_.y, true);
			}


			numberOfTiles++;
		}
	}
	tile_selected_ = &(*tiles_.begin());
	tile_selected_->Deselect();
	std::cout << "Total tiles: " << numberOfTiles << std::endl;
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
	sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	// Snap mouse position to the grid
	sf::Vector2f mousePosition(
		static_cast<int>(worldPos.x / playground_tile_size_u_.x) * playground_tile_size_u_.x,
		static_cast<int>(worldPos.y / playground_tile_size_u_.y) * playground_tile_size_u_.y
	);


	auto tileFound = std::find_if(tiles_.begin(), tiles_.end(), [&mousePosition](Tile& t) {return t.Position() == mousePosition; });

	if (tileFound != tiles_.end())
	{
		//TODO: Could put the hover_tile here, aka the Tile could manage the hover itself (That's what Select does)
		tile_selected_ = &(*tileFound);
		tile_selected_->Select();
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		//Check if the left mouse button is pressed
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (clicked_tile_ && tile_selected_) {
				clicked_tile_(*tile_selected_);
				std::cout << static_cast<int>(GetSelectedTileType()) << std::endl;
			}
			else
			{
				std::cout << "No callback defined." << std::endl;
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

TileType Tilemap::GetSelectedTileType() const {
	if (tile_selected_) {
		return tile_selected_->type(); // Assuming Tile class has a GetType() method
	}
	else {
		return TileType::kPlain;
	}
}

void Tilemap::applyFadeEffect(sf::RenderTarget& target)
{
	sf::View view = target.getView();
	sf::Vector2f viewCenter = view.getCenter();
	sf::FloatRect viewBounds(
		viewCenter - view.getSize() / 2.f,
		view.getSize()
	);

	float maxDistance = std::max(viewBounds.width, viewBounds.height) / 2.f;

	for (auto& tile : tiles_)
	{
		sf::FloatRect tileBounds(
			tile.Position().x,
			tile.Position().y,
			static_cast<float>(playground_tile_size_u_.x),
			static_cast<float>(playground_tile_size_u_.y)
		);

		if (viewBounds.intersects(tileBounds))
		{
			float distance = std::hypot(tile.Position().x - viewCenter.x, tile.Position().y - viewCenter.y);
			float fadeFactor = std::clamp(1.0f - (distance / maxDistance), 0.0f, 1.0f);
			sf::Color color = sf::Color(255 * fadeFactor, 255 * fadeFactor, 255 * fadeFactor);
			tile.setColor(color);
		}
	}
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	const_cast<Tilemap*>(this)->applyFadeEffect(target);

	for (const auto& tile : tiles_)
	{
		target.draw(tile, states);
	}
}
