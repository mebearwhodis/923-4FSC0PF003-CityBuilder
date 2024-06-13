#ifndef API_UI_CURSOR_H_
#define API_UI_CURSOR_H_
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Window.hpp>

class CursorChange
{
	//TODO Move cursors to resource manager
	static void BasicCursor(sf::Window& window)
	{
		sf::Image cursorImage;
		cursorImage.loadFromFile("../resources/sprites/ui/cursorGauntlet_blue.png");
		sf::Cursor cursor;
		cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), { 0,0 });

		window.setMouseCursor(cursor);
	}

	static void BuildCursor(sf::Window& window)
	{
		sf::Image cursorImage;
		cursorImage.loadFromFile("../resources/sprites/ui/cursorGauntlet_blue.png");
		sf::Cursor cursor;
		cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), { 0,0 });

		window.setMouseCursor(cursor);
	}
};
#endif // CURSOR_H
