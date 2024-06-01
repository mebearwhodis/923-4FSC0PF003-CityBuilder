#include <iostream>
#include <SFML/Graphics.hpp>

#include "api/include/ui/UIButton.h"
#include "graphics/Tilemap.h"

void firstCallback()
{
	std::cout << "button 1 pressed" << std::endl;
}

void secondCallback()
{
	std::cout << "button 2 pressed" << std::endl;
}

int main()
{
	sf::Vector2f tile_size = sf::Vector2f(Tilemap::playground_tile_size_u_.x, Tilemap::playground_tile_size_u_.y);

	//Cursor
	sf::Image cursorImage;
	cursorImage.loadFromFile("../resources/sprites/ui/cursorGauntlet_blue.png");
	sf::Cursor cursor;
	cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), { 0,0 });

	//Hovered tile frame
	sf::RectangleShape hovered_tile;
	hovered_tile.setSize(tile_size);
	hovered_tile.setFillColor(sf::Color(100, 100, 100, 180));
	hovered_tile.setOutlineColor(sf::Color::Magenta);
	hovered_tile.setOutlineThickness(-1);
	hovered_tile.setOrigin(0, 0);

	Tilemap map = Tilemap(sf::Vector2u(200, 200));

	//Create the window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

	//Basic Setup of the window
	//Vertical sync, framerate, cursor
	window.setMouseCursor(cursor);
	window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);
	//window.setMouseCursorVisible(false);

	//Create buttons
	UiButton firstButton(sf::Vector2f(400, 400), sf::Color::Cyan, "Generate", ResourceManager::Resource::WhiteButtonRedFrame);

	UiButton secondButton(sf::Vector2f(400, 200), sf::Color::Cyan, "Bouton 2", ResourceManager::Resource::WhiteButtonRedFrame);


	//Use a lambda to attach method to button
	firstButton.callback_ = [&map]() {
		map.Generate();
		};

	secondButton.callback_ = secondCallback;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		sf::Vector2i mouse_tile_coord(mouse_pos.x / tile_size.x, mouse_pos.y / tile_size.y);
		hovered_tile.setPosition(mouse_tile_coord.x * tile_size.x, mouse_tile_coord.y * tile_size.y);

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			// Handle UI Events
			firstButton.HandleEvent(event);
			secondButton.HandleEvent(event);

		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);
		window.draw(map);

		window.draw(hovered_tile);


		window.draw(firstButton);
		window.draw(secondButton);

		// end the current frame
		window.display();
	}

	return 0;
}
