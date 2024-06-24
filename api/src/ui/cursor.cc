// cursor.cpp

#include "ui/cursor.h"

Cursor::Cursor() {}

void Cursor::changeCursor(CursorType cursor, sf::RenderWindow& window) {
    // Load cursor image from ResourceManager
    cursorImage = ResourceManager::Get().GetCursorImage(cursor);

    // Create SFML Cursor object from loaded image
    cursor_.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), { 0, 0 });

    // Set SFML window cursor
    window.setMouseCursor(cursor_);
}
