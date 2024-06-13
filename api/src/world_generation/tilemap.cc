#include "world_generation/tilemap.h"

#include <random>
#include <SFML/Graphics/RenderTarget.hpp>

//TODO Check "Setup" on the repo
// Fix 1 : initiate static in the cc file
sf::Vector2u Tilemap::playground_size_u_ = sf::Vector2u(50, 50);
sf::Vector2u Tilemap::playground_tile_size_u_ = sf::Vector2u(64, 64);

void Tilemap::Generate()
{
	int numberOfTiles = 0;
	tiles_.clear();
	//tiles_.erase(tiles_.begin(), tiles_.end());

	for (unsigned int x = 0; x < playground_size_u_.x; x++)
	{
		for (unsigned int y = 0; y < playground_size_u_.y; y++)
		{
			std::cout << "Add a sprite in the\t(" << x << "," << y << ")\t position." << std::endl;

			int idx = x * playground_size_u_.y + y;

			//TODO Perlin Noise/ WFC/ Whatevs

			//For now, just simple random
			std::random_device r;
			std::default_random_engine e1(r());
			std::uniform_int_distribution<int> uniform_dist(1, 2);

			int rnd = uniform_dist(e1);
			if (rnd == 1)
			{
				//TODO: Replace resource by tiletype
				tiles_.emplace_back(ResourceManager::Resource::kTerrainForest, x * playground_tile_size_u_.x, y * playground_tile_size_u_.y, false);
			}
			if (rnd == 2)
			{
				tiles_.emplace_back(ResourceManager::Resource::kTerrainForestCutDown, x * playground_tile_size_u_.x, y * playground_tile_size_u_.y, true);
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

void Tilemap::HandleEvent(const sf::Event& event)
{
	//Check for mouse move event
	if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mousePosition = sf::Vector2f(
			event.mouseMove.x - event.mouseMove.x % playground_tile_size_u_.x,
			event.mouseMove.y - event.mouseMove.y % playground_tile_size_u_.y
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



void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

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

	for (auto tile : tiles_)
	{
		target.draw(tile, states);
	}
}
