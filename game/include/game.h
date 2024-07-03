#ifndef GAME_GAME_H_
#define GAME_GAME_H_
#include <SFML/Graphics/RenderWindow.hpp>

#include "gameplay/building_manager.h"
#include "world_generation/tilemap.h"
#include "ui/ui_button.h"
#include "graphics/resource_manager.h"
#include "gameplay/view.h"
#include "ui/cursor.h"

class Game {
public:
    Game(); // Constructor declaration
    void init();
    void update();

private:
    sf::RenderWindow window_;
    View game_view_;
    ResourceManager resource_manager_;
    sf::View hud_view_;
    BuildingManager building_manager_;
    Tilemap map_;
    Cursor cursor_manager_;
    sf::Vector2u tile_size_;


    UiButton button_generate_map_;
    UiButton button_clear_map_;
    UiButton button_activate_build_;


    void applyFadeEffect(sf::RenderTarget& target);

};

#endif // GAME_GAME_H_