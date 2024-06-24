#include <iostream>
#include <SFML/Graphics.hpp>

#include "api/include/ui/ui_button.h"
#include "gameplay/building_manager.h"
#include "world_generation/tilemap.h"

#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif


//TODO: Factorize into game class
//TODO: check all #include guards

int main()
{
	#ifdef TRACY_ENABLE
		ZoneScoped;
	#endif
	BuildingManager building_manager;
	auto tile_size = Tilemap::playground_tile_size_u_;

	//Cursor
	sf::Image cursorImage;
	cursorImage.loadFromFile("../resources/sprites/ui/cursorGauntlet_blue.png");
	sf::Cursor cursor;
	cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), { 0,0 });


	Tilemap map = Tilemap(sf::Vector2u(50, 50));

	//Create the window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

	//Basic Setup of the window
	//Vertical sync, framerate, cursor
	window.setMouseCursor(cursor);
	window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);
	//window.setMouseCursorVisible(false);

	//TODO View class + zoom
	//View
	sf::View view_;
	view_.setSize(1920, 1080);
	view_.setCenter(960, 540);

	//Create buttons
	UiButton button_generate_map(sf::Vector2f(400, 100), sf::Color::Cyan, "Generate", ResourceManager::Resource::kWhiteButtonRedFrame);

	UiButton button_clear_map(sf::Vector2f(400, 200), sf::Color::Cyan, "Clear map", ResourceManager::Resource::kWhiteButtonRedFrame);

	UiButton button_activate_build(sf::Vector2f(400, 300), sf::Color::Cyan, "Edit mode", ResourceManager::Resource::kWhiteButtonRedFrame);


	//Use a lambda to attach method to button
	button_generate_map.callback_ = [&map]() {
		map.Generate();
		};

	map.clicked_tile_ = [&building_manager](auto tile) { building_manager.AddBuilding(tile); };


	button_clear_map.callback_ = [&map]() {map.Clear(); };

	button_activate_build.callback_ = [&building_manager]() {building_manager.ToggleActive(); };

	// run the program as long as the window is open
	while (window.isOpen())
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_world_pos = window.mapPixelToCoords(mouse_pos);
		//sf::Vector2i mouse_tile_coord; 
		sf::Vector2f mouse_tile_coord(
			static_cast<int>(mouse_world_pos.x / tile_size.x) * tile_size.x,
			static_cast<int>(mouse_world_pos.y / tile_size.y) * tile_size.y
		);
			

		//sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		//sf::Vector2i mouse_tile_coord(mouse_pos.x / tile_size.x, mouse_pos.y / tile_size.y);
		//hovered_tile.setPosition(mouse_tile_coord.x * tile_size.x, mouse_tile_coord.y * tile_size.y);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//if (view_.getCenter().x - view_.getSize().x / 2 > 0)
			//{
				view_.move(-50.f, 0.f);
			//}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			//if (view_.getCenter().x + view_.getSize().x / 2 < TILE_SIZE * level_width)
			//{
				view_.move(50.f, 0.f);
			//}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			//if (view_.getCenter().x + view_.getSize().x / 2 < TILE_SIZE * level_width)
			//{
			view_.move(0.f, -50.f);
			//}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			//if (view_.getCenter().x + view_.getSize().x / 2 < TILE_SIZE * level_width)
			//{
			view_.move(0.f, 50.f);
			//}
		}

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			// Handle UI Events
			button_generate_map.HandleEvent(event);
			button_clear_map.HandleEvent(event);
			button_activate_build.HandleEvent(event);

			map.HandleEvent(event, window);

		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);
		window.draw(map);

		if(building_manager.IsActive())
		{
			//building_manager.SetHoverTilePosition(sf::Vector2f(static_cast<float>(mouse_tile_coord.x) * tile_size.x, static_cast<float>(mouse_tile_coord.y) * tile_size.y));
			building_manager.SetHoverTilePosition(mouse_tile_coord);
			window.draw(building_manager.HoverTile());
		}

		window.setView(view_);

		window.draw(button_generate_map);
		window.draw(button_clear_map);
		window.draw(button_activate_build);

		// end the current frame
		window.display();
	}

	//In the loop
	#ifdef TRACY_ENABLE
	FrameMark;
	#endif

	return 0;
}
