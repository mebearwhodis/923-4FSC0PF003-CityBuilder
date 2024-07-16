#ifndef GAME_GAME_H_
#define GAME_GAME_H_
#include <SFML/Graphics/RenderWindow.hpp>

#include "gameplay/building_manager.h"
#include "gameplay/economy_manager.h"
#include "world_generation/tilemap.h"
#include "ui/ui_button.h"
#include "graphics/resource_manager.h"
#include "gameplay/view.h"
#include "gameplay/ai/villager_manager.h"
#include "ui/cursor.h"
#include "ui/textbox.h"

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
    VillagerManager villager_manager_;
    EconomyManager economy_manager_;
    Cursor cursor_manager_;
    sf::Vector2u tile_size_;
    void SetCallbacks();
    void CreateTextboxes();


    UiButton button_menu_;
    UiButton button_build_house_;
    UiButton button_build_forge_;
    UiButton button_build_sawmill_;
    UiButton button_build_storage_;
    UiButton gameplay_resources_;
    std::array<UiButton*, 6> buttons_;
    std::array<TextBox, 12> textboxes_ = {};
    bool any_button_pressed_;
};

#endif // GAME_GAME_H_