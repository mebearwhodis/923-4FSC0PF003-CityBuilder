#ifndef GAME_GAME_H_
#define GAME_GAME_H_
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../api/include/gameplay/building_manager.h"
#include "../../api/include/world_generation/tilemap.h"
#include "../../api/include/ui/ui_button.h"
#include "../../api/include/graphics/resource_manager.h"
#include "../../api/include/gameplay/view.h"
#include "../../api/include/ui/cursor.h"

class Game {
public:
    Game(); // Constructor declaration
    void init();
    void update();

private:
    sf::RenderWindow window;
    View game_view_;
    sf::View hud_view_;
    BuildingManager building_manager;
    Tilemap map;
    Cursor cursor_manager_;
    sf::Vector2u tile_size;

    UiButton button_generate_map;
    UiButton button_clear_map;
    UiButton button_activate_build;

};

#endif // GAME_GAME_H_