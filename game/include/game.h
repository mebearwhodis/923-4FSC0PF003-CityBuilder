#ifndef GAME_GAME_H_
#define GAME_GAME_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>>

#include "gameplay/ai/villager_manager.h"
#include "gameplay/building_manager.h"
#include "gameplay/economy_manager.h"
#include "gameplay/view.h"
#include "graphics/resource_manager.h"
#include "ui/cursor.h"
#include "ui/textbox.h"
#include "ui/ui_button.h"
#include "save_system.h"
#include "world_generation/tilemap.h"

class Game
{
public:
    Game();
    void init();
    void update();

private:
    sf::RenderWindow window_;
    sf::Vector2u tile_size_;
    sf::View hud_view_;
    View game_view_;
    sf::Music music_;
    ResourceManager resource_manager_;
    BuildingManager building_manager_;
    VillagerManager villager_manager_;
    EconomyManager economy_manager_;
    SaveSystem save_system_;
    Cursor cursor_manager_;
    Tilemap map_;

    UiButton button_menu_;
    UiButton button_build_house_;
    UiButton button_build_forge_;
    UiButton button_build_sawmill_;
    UiButton button_build_storage_;
    UiButton gameplay_resources_;

    std::array<UiButton*, 6> ui_elements_;
    std::array<TextBox, 12> textboxes_ = {};
    bool any_button_pressed_;

    void SetCallbacks();
    void CreateTextboxes();
    void UpdateTextboxes();
};
#endif // GAME_GAME_H_