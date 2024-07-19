#ifndef API_UI_CURSOR_H_
#define API_UI_CURSOR_H_

#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Cursor.hpp>

#include "graphics/resource_manager.h"

class Cursor
{
private:
    sf::Cursor cursor_;
    sf::Image cursor_image_;

public:
    Cursor();

    void ChangeCursor(CursorType cursor, sf::RenderWindow& window);
};
#endif // API_UI_CURSOR_H_