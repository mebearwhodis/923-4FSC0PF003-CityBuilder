#include <iostream>
#include <SFML/Graphics.hpp>

#include "api/include/ui/ui_button.h"
#include "gameplay/building_manager.h"
#include "world_generation/tilemap.h"


int main()
{

	BuildingManager building_manager;
	sf::Vector2f tile_size = sf::Vector2f(Tilemap::playground_tile_size_u_.x, Tilemap::playground_tile_size_u_.y);

	//Cursor
	sf::Image cursorImage;
	cursorImage.loadFromFile("../resources/sprites/ui/cursorGauntlet_blue.png");
	sf::Cursor cursor;
	cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), { 0,0 });

	//Hovered tile frame
	//sf::RectangleShape hovered_tile;
	//hovered_tile.setSize(tile_size);
	//hovered_tile.setFillColor(sf::Color(100, 100, 100, 180));
	//hovered_tile.setOutlineColor(sf::Color::Magenta);
	//hovered_tile.setOutlineThickness(-1);
	//hovered_tile.setOrigin(0, 0);
	//bool display_hover = false;

	Tilemap map = Tilemap(sf::Vector2u(50, 50));

	//Create the window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

	//Basic Setup of the window
	//Vertical sync, framerate, cursor
	window.setMouseCursor(cursor);
	window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);
	//window.setMouseCursorVisible(false);

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
		sf::Vector2i mouse_tile_coord;


		//TODO: C'est moche et temporaire, peut-être y'a moyen de moyenner avec un arrondi correct
		if(mouse_world_pos.x < 0 && mouse_world_pos.y < 0)
		{
			mouse_tile_coord = sf::Vector2i((mouse_world_pos.x / tile_size.x) -1, (mouse_world_pos.y / tile_size.y) -1);
		}
		else if(mouse_world_pos.x < 0)
		{
			mouse_tile_coord = sf::Vector2i((mouse_world_pos.x / tile_size.x) -1, mouse_world_pos.y / tile_size.y);
		}else if(mouse_world_pos.y < 0)
		{
			mouse_tile_coord = sf::Vector2i(mouse_world_pos.x / tile_size.x, (mouse_world_pos.y / tile_size.y) -1);
		}
		else
		{
			mouse_tile_coord = sf::Vector2i(mouse_world_pos.x / tile_size.x, mouse_world_pos.y / tile_size.y);
		}


		

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

			map.HandleEvent(event);

		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);
		window.draw(map);

		if(building_manager.IsActive())
		{
			building_manager.SetHoverTilePosition(sf::Vector2f(static_cast<float>(mouse_tile_coord.x) * tile_size.x, static_cast<float>(mouse_tile_coord.y) * tile_size.y));
			window.draw(building_manager.HoverTile());
		}

		window.setView(view_);

		window.draw(button_generate_map);
		window.draw(button_clear_map);
		window.draw(button_activate_build);

		// end the current frame
		window.display();
	}

	return 0;
}
