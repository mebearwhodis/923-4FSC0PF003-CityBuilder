#include "ui/cursor.h"

Cursor::Cursor() = default;

void Cursor::ChangeCursor(const CursorType cursor, sf::RenderWindow& window) {
    // Load cursor image from ResourceManager
    cursor_image_ = ResourceManager::Get().GetCursorImage(cursor);

    // Create SFML Cursor object from loaded image
    cursor_.loadFromPixels(cursor_image_.getPixelsPtr(), cursor_image_.getSize(), { 0, 0 });

    // Set SFML window cursor
    window.setMouseCursor(cursor_);
}
