#include "game.h"

#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif

#include "gameplay/ai/woodsman.h"
#include "pathfinding/pathfinder.h"

//TODO ajouter stockage, au moment de ramener les ressources, cherche le stockage le plus proche pour y ramener les éléments -> hence, nécessité de créer des stockages proches


Game::Game() :
	window_(sf::VideoMode(1920, 1080), "My window"),
	game_view_(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080)),
	button_menu_(sf::Vector2f(100, 100), sf::Color::Cyan, " ", UiTexture::kMenuUp, true),
	button_build_house_(sf::Vector2f(100, 155), sf::Color::Cyan, " ", UiTexture::kHouseUp, false),
	button_build_forge_(sf::Vector2f(100, 210), sf::Color::Cyan, " ", UiTexture::kForgeUp, false),
	button_build_sawmill_(sf::Vector2f(100, 265), sf::Color::Cyan, " ", UiTexture::kSawmillUp, false),
	buttons_{&button_menu_, &button_build_house_, &button_build_forge_, &button_build_sawmill_},
	any_button_pressed_(false)
{
}


void Game::init() {
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	std::srand(std::time(nullptr));
	// Basic Setup of the window
	window_.setFramerateLimit(60);
	window_.setVerticalSyncEnabled(true);

	hud_view_ = sf::View(sf::FloatRect(0, 0, 1920, 1080));

	// Set initial cursor
	cursor_manager_.changeCursor(CursorType::kArrow, window_);

	tile_size_ = sf::Vector2u(64,64);
	map_.Setup(sf::Vector2u(100, 100), tile_size_);
	map_.Generate();


	// Center the view to the middle of the tilemap
	sf::Vector2f map_size(map_.playground_size_u().x * tile_size_.x, map_.playground_size_u().y * tile_size_.y);
	const sf::Vector2f map_center(map_size.x / 2.0f, map_size.y / 2.0f);
	game_view_.setCenter(map_center);
	game_view_.setBounds(sf::FloatRect(0, 0, map_size.x, map_size.y));


	map_.clicked_tile_ = [this](Tile& tile) {
		std::cout << "Tile clicked:\t" << tile.Position().x << "/" << tile.Position().y << "\t" << std::endl;
		//TODO Add check to stop from adding buildings if not enough resources and/or if current pop = total pop
		if(building_manager_.AddBuilding(tile))
		{
			switch (building_manager_.building_type())
			{
			case TileType::kHouse:
				total_population_ += 2;
				break;
			case TileType::kForge:
				current_population_ += 1;
				break;
			case TileType::kSawmill:
				villager_manager_.SpawnVillager(tile, map_, VillagerType::kWoodsman);
				current_population_ += 1;
				break;
			default:
				break;
			}
		}
		std::cout << current_population_ << std::endl;
		};

	// Set button callbacks
	//button_generate_map_.callback_ = [this]() {
	//	map_.Generate();
	//	};

	//button_clear_map_.callback_ = [this]() {
	//	map_.Clear();
	//	building_manager_.ClearBuildings();
	//	};

	button_menu_.callback_ = [this]()
		{
			building_manager_.ToggleActive();
			button_build_house_.toggle_visible();
			button_build_forge_.toggle_visible();
			button_build_sawmill_.toggle_visible();

			if (building_manager_.IsActive())
			{
				cursor_manager_.changeCursor(CursorType::kBuild, window_);
			}
			else
			{
				cursor_manager_.changeCursor(CursorType::kArrow, window_);
			}
		};

	button_build_house_.callback_ = [this]()
		{
			building_manager_.set_building_type(TileType::kHouse);
		};

	button_build_forge_.callback_ = [this]()
		{
			building_manager_.set_building_type(TileType::kForge);
		};

	button_build_sawmill_.callback_ = [this]()
		{
			building_manager_.set_building_type(TileType::kSawmill);
		};
}


void Game::update() {
	//Woodsman A* test
	//tile_size_ = sf::Vector2u(64, 64);
	//sf::Vector2f map_size(map_.playground_size_u().x * tile_size_.x, map_.playground_size_u().y * tile_size_.y);
	//const sf::Vector2f map_center(map_size.x / 2.0f, map_size.y / 2.0f);
	//Woodsman billy(map_center.x, map_center.y, 128, map_);

	//Pathfinder pathfinder;
	

	// run the program as long as the window is open
	while (window_.isOpen()) {

		//TODO Have an AI_manager with vectors of ai and Tick() for each of them
		/*billy.Tick();*/
		villager_manager_.Tick();

		game_view_.apply(window_);
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
		sf::Vector2f mouse_world_pos = window_.mapPixelToCoords(mouse_pos);
		sf::Vector2f mouse_tile_coord(
			static_cast<int>(mouse_world_pos.x / tile_size_.x) * tile_size_.x,
			static_cast<int>(mouse_world_pos.y / tile_size_.y) * tile_size_.y
		);

		game_view_.handleInput(window_);
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window_.pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window_.close();

			//if (event.type == sf::Event::MouseButtonReleased)
			//{
			//	//Check if the right mouse button is pressed
			//	if (event.mouseButton.button == sf::Mouse::Right)
			//	{
			//		sf::Vector2f destination(mouse_tile_coord);
			//		Path p = Pathfinder::CalculatePath(map_.GetWalkableTiles(), billy.GetLastDestination(), destination, 64);
			//		billy.set_path(p);
			//		//Woodsman billy(mouse_tile_coord.x, mouse_tile_coord.y, 1280, map_);
			//	}
			//}

			game_view_.handleEvent(event, window_);

			//Don't trigger event on map if clicking a button
			for (const auto button : buttons_)
			{
				if(button->is_visible())
				{
					if (button->ContainsMouse(event.mouseButton))
					{
						button->HandleEvent(event);
						any_button_pressed_ = true;
						break;
					}
					any_button_pressed_ = false;
				}
			}
			if(!any_button_pressed_)
			{
				map_.HandleEvent(event, window_);
			}
		}

		// clear the window with black color
		window_.clear(sf::Color::Black);

		// draw everything here...
		window_.draw(map_);
		window_.draw(building_manager_);
		window_.draw(villager_manager_);

		if (building_manager_.IsActive()) {
			if (map_.GetSelectedTileType() == TileType::kPlain)
			{
				building_manager_.ChangeHoverTileColour(sf::Color(100, 255, 100, 200));
			}
			else
			{
				building_manager_.ChangeHoverTileColour(sf::Color(255, 100, 100, 200));
			}
			building_manager_.SetHoverTilePosition(mouse_tile_coord);
			window_.draw(building_manager_.HoverTile());
		}

		//TEST
		//window_.draw(billy);

		window_.setView(hud_view_);

		for (const auto button : buttons_)
		{
				window_.draw(*button);
		}

		// end the current frame
		window_.display();

#ifdef TRACY_ENABLE
		FrameMark;
#endif
	}
}