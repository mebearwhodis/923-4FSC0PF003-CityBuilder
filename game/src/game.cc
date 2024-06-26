#include "game.h"

#include <Tracy/Tracy.hpp>

#include "../../api/include/gameplay/ai/woodsman.h"


Game::Game()
	: window_(sf::VideoMode(1920, 1080), "My window"),
	game_view_(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080)),
	button_generate_map_(sf::Vector2f(1920 / 4, 200), sf::Color::Cyan, "Generate", UiTexture::kWhiteButtonRedFrame),
	button_clear_map_(sf::Vector2f(1920 / 4, 400), sf::Color::Cyan, "Clear map", UiTexture::kWhiteButtonRedFrame),
	button_activate_build_(sf::Vector2f(1920 / 4, 600), sf::Color::Cyan, "Edit mode", UiTexture::kWhiteButtonRedFrame)
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
	cursor_manager_.changeCursor(CursorType::kBasic, window_);

	tile_size_ = sf::Vector2u(64, 64);
	map_.Setup(sf::Vector2u(200, 200), tile_size_);

	// Center the view to the middle of the tilemap
	sf::Vector2f map_size(map_.playground_size_u().x * tile_size_.x, map_.playground_size_u().y * tile_size_.y);
	const sf::Vector2f map_center(map_size.x / 2.0f, map_size.y / 2.0f);
	game_view_.setCenter(map_center);
	game_view_.setBounds(sf::FloatRect(0, 0, map_size.x, map_size.y));


	map_.clicked_tile_ = [this](auto tile) {
		std::cout << "Tile clicked:\t" << tile.Position().x << "/" << tile.Position().y << "\t" << std::endl;
		building_manager_.AddBuilding(tile);
		};

	// Set button callbacks
	button_generate_map_.callback_ = [this]() {
		map_.Generate();
		};

	button_clear_map_.callback_ = [this]() {
		map_.Clear();
		//TODO clear buildings list
		};

	button_activate_build_.callback_ = [this]() {
		building_manager_.ToggleActive();
		if (building_manager_.IsActive())
		{
			cursor_manager_.changeCursor(CursorType::kGauntlet, window_);
		}
		else
		{

			cursor_manager_.changeCursor(CursorType::kBasic, window_);
		}
		};

}


void Game::update() {

	Woodsman billy(12800/2, 12800/2, 64);
	

	// run the program as long as the window is open
	while (window_.isOpen()) {

		billy.Tick();
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

			// Handle UI Events
			button_generate_map_.HandleEvent(event);
			button_clear_map_.HandleEvent(event);
			button_activate_build_.HandleEvent(event);

			map_.HandleEvent(event, window_);
			game_view_.handleEvent(event, window_);
		}

		// clear the window with black color
		window_.clear(sf::Color::Black);

		// draw everything here...
		window_.draw(map_);
		window_.draw(building_manager_);

		if (building_manager_.IsActive()) {
			building_manager_.SetHoverTilePosition(mouse_tile_coord);
			window_.draw(building_manager_.HoverTile());
		}

		//TEST
		window_.draw(billy);

		window_.setView(hud_view_);

		window_.draw(button_generate_map_);
		window_.draw(button_clear_map_);
		window_.draw(button_activate_build_);


		// end the current frame
		window_.display();
	}
}