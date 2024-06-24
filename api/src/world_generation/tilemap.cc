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
	std::uniform_int_distribution<int> uniform_dist(1, 2);

	for (unsigned int x = 0; x < playground_size_u_.x; x++)
	{
		for (unsigned int y = 0; y < playground_size_u_.y; y++)
		{


			int idx = x * playground_size_u_.y + y;

			//TODO Perlin Noise/ WFC/ Whatevs


			int rnd = uniform_dist(e1);

			if (rnd == 1)
			{
				//TODO: Replace resource by tiletype
				tiles_.emplace_back(Resource::kTerrainForest, x * playground_tile_size_u_.x, y * playground_tile_size_u_.y, false);
			}
			if (rnd == 2)
			{
				tiles_.emplace_back(Resource::kTerrainForestCutDown, x * playground_tile_size_u_.x, y * playground_tile_size_u_.y, true);
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
	//Check for mouse move event
	//TODO: This is not necessary -> check if it's worth to keep. The outline movement is more fluid without this
	if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		// Snap mouse position to the grid
		sf::Vector2f mousePosition(
			static_cast<int>(worldPos.x / playground_tile_size_u_.x) * playground_tile_size_u_.x,
			static_cast<int>(worldPos.y / playground_tile_size_u_.y) * playground_tile_size_u_.y
		);

		//TODO find why it bugs when using this rather than the for_each
		//if (tile_selected_)
		//{
		//	tile_selected_->Deselect();
		//}

		std::for_each(tiles_.begin(), tiles_.end(), [](Tile& t) {t.Deselect(); });

		auto tileFound = std::find_if(tiles_.begin(), tiles_.end(), [&mousePosition](Tile& t) {return t.Position() == mousePosition; });

		if (tileFound != tiles_.end())
		{
			//TODO: Could put the hover_tile here, aka the Tile could manage the hover itself (That's what Select does)
			tile_selected_ = &(*tileFound);
			tile_selected_->Select();
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		//Check if the left mouse button is pressed
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (clicked_tile_ && tile_selected_) {
				clicked_tile_(*tile_selected_);
			}
			else
			{
				std::cout << "No callback defined.";
			}
		}
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


	//TODO: use that to draw only what's in the view -> make a view class, probably. Can also make a "fog of war" kind of thing, the further it is from the center of the view, the more obscured it is (and then not display at all if out of the view)
	//auto tile = tiles_.begin();
	//
	//while (tile != tiles_.end())
	//{
	//	tile = std::find_if(tile, tiles_.end(), [](const Tile& t) {return t.Walkable(); });
	//	if (tile != tiles_.end())
	//	{
	//		target.draw(*tile, states);
	//		++tile;
	//	}
	//}



	//for (auto tile : tiles_)
	//{
	//	target.draw(tile, states);
	//}
}
