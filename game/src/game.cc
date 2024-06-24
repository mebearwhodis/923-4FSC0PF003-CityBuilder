#include "game.h"


//TODO View class + zoom

Game::Game()
    : window(sf::VideoMode(1920, 1080), "My window"),
    view_(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080)),
    map(sf::Vector2u(50, 50)),
    button_generate_map(sf::Vector2f(400, 100), sf::Color::Cyan, "Generate", ResourceManager::Resource::kWhiteButtonRedFrame),
    button_clear_map(sf::Vector2f(400, 200), sf::Color::Cyan, "Clear map", ResourceManager::Resource::kWhiteButtonRedFrame),
    button_activate_build(sf::Vector2f(400, 300), sf::Color::Cyan, "Edit mode", ResourceManager::Resource::kWhiteButtonRedFrame)
{
    tile_size = Tilemap::playground_tile_size_u_;
}


void Game::init() {
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif

    std::cout << "Initializing game..." << std::endl;

    // Cursor
    sf::Image cursorImage;
    if (!cursorImage.loadFromFile("../resources/sprites/ui/cursorGauntlet_blue.png")) {
        std::cerr << "Failed to load cursor image!" << std::endl;
    }
    cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), { 0,0 });
    window.setMouseCursor(cursor);

    // Basic Setup of the window
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);

    // Set button callbacks
    button_generate_map.callback_ = [this]() {
        std::cout << "Generate map button clicked" << std::endl;
        map.Generate();
        };

    map.clicked_tile_ = [this](auto tile) {
        std::cout << "Tile clicked" << std::endl;
        building_manager.AddBuilding(tile);
        };

    button_clear_map.callback_ = [this]() {
        std::cout << "Clear map button clicked" << std::endl;
        map.Clear();
        };

    button_activate_build.callback_ = [this]() {
        std::cout << "Activate build button clicked" << std::endl;
        building_manager.ToggleActive();
        };
}

void Game::update() {
    std::cout << "Starting update loop..." << std::endl;

    // run the program as long as the window is open
    while (window.isOpen()) {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_world_pos = window.mapPixelToCoords(mouse_pos);
        sf::Vector2f mouse_tile_coord(
            static_cast<int>(mouse_world_pos.x / tile_size.x) * tile_size.x,
            static_cast<int>(mouse_world_pos.y / tile_size.y) * tile_size.y
        );

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            view_.move(-50.f, 0.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            view_.move(50.f, 0.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view_.move(0.f, -50.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view_.move(0.f, 50.f);
        }

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
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(map);

        if (building_manager.IsActive()) {
            building_manager.SetHoverTilePosition(mouse_tile_coord);
            window.draw(building_manager.HoverTile());
        }

        window.setView(view_);

        window.draw(button_generate_map);
        window.draw(button_clear_map);
        window.draw(button_activate_build);

        // end the current frame
        window.display();
    }
}