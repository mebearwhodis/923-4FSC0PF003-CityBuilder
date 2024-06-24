#include "game.h"


Game::Game()
    : window(sf::VideoMode(1920, 1080), "My window"),
    view_(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080)),
    map(),
    button_generate_map(sf::Vector2f(1920/4, 200), sf::Color::Cyan, "Generate", Resource::kWhiteButtonRedFrame),
	button_clear_map(sf::Vector2f(1920 / 4, 400), sf::Color::Cyan, "Clear map", Resource::kWhiteButtonRedFrame),
	button_activate_build(sf::Vector2f(1920 / 4, 600), sf::Color::Cyan, "Edit mode", Resource::kWhiteButtonRedFrame)
{
}


void Game::init() {
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif

    // Basic Setup of the window
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);

    // Set initial cursor
    cursor_manager_.changeCursor(CursorType::kBasic, window);

    map.Setup(sf::Vector2u(200, 200), sf::Vector2u(64, 64));
    tile_size = sf::Vector2u(64, 64);

    map.clicked_tile_ = [this](auto tile) {
        std::cout << "Tile clicked" << std::endl;
        building_manager.AddBuilding(tile);
        };

    // Set button callbacks
    button_generate_map.callback_ = [this]() {
        map.Generate();
        };

    button_clear_map.callback_ = [this]() {
        map.Clear();
        };

    button_activate_build.callback_ = [this]() {
        building_manager.ToggleActive();
        if(building_manager.IsActive())
        {
            cursor_manager_.changeCursor(CursorType::kGauntlet, window);
        }else
        {

            cursor_manager_.changeCursor(CursorType::kBasic, window);
        }
        };


    buttons_.push_back(button_generate_map);
    buttons_.push_back(button_clear_map);
    buttons_.push_back(button_activate_build);
}

void Game::update() {

    // run the program as long as the window is open
    while (window.isOpen()) {

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_world_pos = window.mapPixelToCoords(mouse_pos);
        sf::Vector2f mouse_tile_coord(
            static_cast<int>(mouse_world_pos.x / tile_size.x) * tile_size.x,
            static_cast<int>(mouse_world_pos.y / tile_size.y) * tile_size.y
        );

        view_.handleInput(window);
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle UI Events
            button_generate_map.HandleEvent(event);
            button_clear_map.HandleEvent(event);
            button_activate_build.HandleEvent(event);

            map.HandleEvent(event, window);
            view_.handleEvent(event);
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        view_.apply(window);

        // draw everything here...
        window.draw(map);

        if (building_manager.IsActive()) {
            building_manager.SetHoverTilePosition(mouse_tile_coord);
            window.draw(building_manager.HoverTile());
        }

        window.draw(button_generate_map);
        window.draw(button_clear_map);
        window.draw(button_activate_build);

        // end the current frame
        window.display();
    }
}