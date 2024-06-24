#ifndef API_UI_CURSOR_H_
#define API_UI_CURSOR_H_
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Cursor.hpp>

#include "../graphics/resource_manager.h"


class Cursor {
public:
    Cursor();

    void changeCursor(CursorType cursor, sf::RenderWindow& window);

private:
    sf::Cursor cursor_;
    sf::Image cursorImage;
};

#endif // API_UI_CURSOR_H_