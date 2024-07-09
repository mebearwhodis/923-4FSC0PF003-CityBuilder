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
    Tilemap map_;
    BuildingManager building_manager_;
    Cursor cursor_manager_;
    sf::Vector2u tile_size_;

    int current_population_ = 0;
    int total_population_ = 0;

    UiButton button_menu_;
    UiButton button_build_house_;
    UiButton button_build_forge_;
    UiButton button_build_sawmill_;
    std::array<UiButton*, 4> buttons_;
    bool any_button_pressed_;
};

#endif // GAME_GAME_H_