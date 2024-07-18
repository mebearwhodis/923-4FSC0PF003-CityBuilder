#include "game.h"

#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif


Game::Game() :
	window_(sf::VideoMode(1920, 1080), "Little people gathering little resources"),
	game_view_(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080)),
	button_menu_(sf::Vector2f(100, 100), sf::Color::Cyan, UiTexture::kMenuUp, true),
	button_build_house_(sf::Vector2f(100, 155), sf::Color::Cyan, UiTexture::kHouseUp, false),
	button_build_forge_(sf::Vector2f(100, 210), sf::Color::Cyan, UiTexture::kForgeUp, false),
	button_build_sawmill_(sf::Vector2f(100, 265), sf::Color::Cyan, UiTexture::kSawmillUp, false),
	button_build_storage_(sf::Vector2f(100, 320), sf::Color::Cyan, UiTexture::kStorageUp, false),
	gameplay_resources_(sf::Vector2f(1820, 100), sf::Color::Cyan, UiTexture::kGameplayResourcesUp, true),
	ui_elements_{ &button_menu_, &button_build_house_, &button_build_forge_, &button_build_sawmill_, &button_build_storage_, &gameplay_resources_ },
	any_button_pressed_(false)
{

}


void Game::init() {
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	std::srand(std::time(nullptr));
	// Basic Setup of the window
	window_.setFramerateLimit(60);
	window_.setVerticalSyncEnabled(true);

	hud_view_ = sf::View(sf::FloatRect(0, 0, 1920, 1080));

	// Set initial cursor
	cursor_manager_.changeCursor(CursorType::kArrow, window_);

	tile_size_ = sf::Vector2u(64, 64);
	map_.Setup(sf::Vector2u(100, 100), tile_size_);
	map_.Generate();


	// Center the view to the middle of the tilemap
	const sf::Vector2f map_size(map_.playground_size_u().x * tile_size_.x, map_.playground_size_u().y * tile_size_.y);
	const sf::Vector2f map_center(map_size.x / 2.0f, map_size.y / 2.0f);
	game_view_.setCenter(map_center);
	game_view_.setBounds(sf::FloatRect(0, 0, map_size.x, map_size.y));

	SetCallbacks();
	CreateTextboxes();
}


void Game::update() {

	while (window_.isOpen()) {

		game_view_.apply(window_);
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
		const sf::Vector2f mouse_world_pos = window_.mapPixelToCoords(mouse_pos);
		const sf::Vector2f mouse_tile_coord(
			static_cast<int>(mouse_world_pos.x / tile_size_.x) * tile_size_.x,
			static_cast<int>(mouse_world_pos.y / tile_size_.y) * tile_size_.y
		);

		villager_manager_.Tick(economy_manager_);
		if(economy_manager_.text_to_update())
		{
			UpdateTextboxes();
		}
		map_.Tick();

		game_view_.handleInput(window_);
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window_.pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window_.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
			{
				save_system_.SaveGame(map_, building_manager_, economy_manager_, "save1.json");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
			{
				save_system_.LoadGame(map_,"save1.json");
			}

			game_view_.handleEvent(event, window_);

			//Don't trigger event on map if clicking a button
			for (const auto button : ui_elements_)
			{
				if (button->is_visible())
				{
					if (button->ContainsMouse(event.mouseButton))
					{
						button->HandleEvent(event);
						any_button_pressed_ = true;
						break;
					}
					any_button_pressed_ = false;
				}
			}
			if (!any_button_pressed_)
			{
				map_.HandleEvent(event, window_);
			}
		}

		// clear the window with black color
		window_.clear(sf::Color::Black);

		// draw everything here...
		window_.draw(map_);
		window_.draw(villager_manager_);
		window_.draw(building_manager_);

		if (building_manager_.IsActive()) {
			if (map_.GetSelectedTileType() == TileType::kPlain)
			{
				building_manager_.ChangeHoverTileColour(sf::Color(100, 255, 100, 200));
			}
			else
			{
				building_manager_.ChangeHoverTileColour(sf::Color(255, 100, 100, 200));
			}
			building_manager_.SetHoverTilePosition(mouse_tile_coord);
			window_.draw(building_manager_.HoverTile());
		}

		window_.setView(hud_view_);

		for (const auto& button : ui_elements_)
		{
			window_.draw(*button);
		}

		for (const auto& textbox : textboxes_)
		{
			window_.draw(textbox);
		}

		// end the current frame
		window_.display();

#ifdef TRACY_ENABLE
		FrameMark;
#endif
	}
}

void Game::SetCallbacks()
{
	map_.clicked_tile_ = [&](Tile& tile) {
		//std::cout << "Tile clicked:\t" << tile.Position().x << "/" << tile.Position().y << "\t" << std::endl;
		if (economy_manager_.current_population() == economy_manager_.total_population() && building_manager_.building_type() != TileType::kHouse)
		{
			return;
		}

		if (building_manager_.AddBuilding(tile, map_))
		{
			int new_house_cost;
			int new_forge_cost;
			int new_sawmill_cost;
			int new_storage_cost;

			switch (building_manager_.building_type())
			{
			case TileType::kHouse:
				economy_manager_.AddTotalPopulation(2);
				economy_manager_.AddWood(-1 * economy_manager_.current_house_cost());
				economy_manager_.AddFood(-1 * economy_manager_.current_house_cost());
				new_house_cost = std::floor(economy_manager_.current_house_cost() * economy_manager_.cost_multiplier());
				if(new_house_cost >= 999)
				{
					new_house_cost = 999;
				}
				economy_manager_.set_current_house_cost(new_house_cost);
				break;
			case TileType::kForge:
				villager_manager_.SpawnVillager(tile.Position(), map_, VillagerType::kMiner);
				economy_manager_.AddPopulation(1);
				economy_manager_.AddWood(-1 * economy_manager_.current_forge_cost());
				economy_manager_.AddStone(-1 * economy_manager_.current_forge_cost());
				new_forge_cost = std::floor(economy_manager_.current_forge_cost() * economy_manager_.cost_multiplier());
				if (new_forge_cost >= 999)
				{
					new_forge_cost = 999;
				}
				economy_manager_.set_current_forge_cost(new_forge_cost);
				break;
			case TileType::kSawmill:
				villager_manager_.SpawnVillager(tile.Position(), map_, VillagerType::kWoodsman);
				economy_manager_.AddPopulation(1);
				economy_manager_.AddWood(-1 * economy_manager_.current_sawmill_cost());
				economy_manager_.AddStone(-1 * economy_manager_.current_sawmill_cost());
				new_sawmill_cost = std::floor(economy_manager_.current_sawmill_cost() * economy_manager_.cost_multiplier());
				if (new_sawmill_cost >= 999)
				{
					new_sawmill_cost = 999;
				}
				economy_manager_.set_current_sawmill_cost(new_sawmill_cost);
				break;
			case TileType::kStorage:
				villager_manager_.SpawnVillager(tile.Position(), map_, VillagerType::kGatherer);
				economy_manager_.AddPopulation(1);
				economy_manager_.AddWood(-1 * economy_manager_.current_storage_cost());
				economy_manager_.AddStone(-1 * economy_manager_.current_storage_cost());
				new_storage_cost = std::floor(economy_manager_.current_storage_cost() * economy_manager_.cost_multiplier());
				if (new_storage_cost >= 999)
				{
					new_storage_cost = 999;
				}
				economy_manager_.set_current_storage_cost(new_storage_cost);
				break;
			default:
				break;
			}
			economy_manager_.set_text_to_update(true);
			building_manager_.set_building_type(TileType::kPlain);
		}
		};

	button_menu_.callback_ = [&]()
		{
			building_manager_.set_building_type(TileType::kPlain);
			building_manager_.ToggleActive();
			button_build_house_.toggle_visible();
			button_build_forge_.toggle_visible();
			button_build_sawmill_.toggle_visible();
			button_build_storage_.toggle_visible();
			for (auto& textbox : textboxes_)
			{
				if (textbox.can_be_hidden())
				{
					textbox.toggle_visible();
				}
			}

			if (building_manager_.IsActive())
			{
				cursor_manager_.changeCursor(CursorType::kBuild, window_);
			}
			else
			{
				cursor_manager_.changeCursor(CursorType::kArrow, window_);
			}
		};

	button_build_house_.callback_ = [&]()
		{
			if (economy_manager_.wood() < economy_manager_.current_house_cost() || economy_manager_.food() < economy_manager_.current_house_cost())
			{
				return;
			}
			else
			{
				building_manager_.set_building_type(TileType::kHouse);
			}
		};

	button_build_forge_.callback_ = [&]()
		{
			if (economy_manager_.wood() < economy_manager_.current_forge_cost() || economy_manager_.stone() < economy_manager_.current_forge_cost() || economy_manager_.current_population() == economy_manager_.total_population())
			{
				return;
			}
			else
			{
				building_manager_.set_building_type(TileType::kForge);
			}
		};

	button_build_sawmill_.callback_ = [&]()
		{
			if (economy_manager_.wood() < economy_manager_.current_sawmill_cost() || economy_manager_.stone() < economy_manager_.current_sawmill_cost() || economy_manager_.current_population() == economy_manager_.total_population())
			{
				return;
			}
			else
			{
				building_manager_.set_building_type(TileType::kSawmill);
			}
		};

	button_build_storage_.callback_ = [&]()
		{
			if (economy_manager_.wood() < economy_manager_.current_storage_cost() || economy_manager_.stone() < economy_manager_.current_storage_cost() || economy_manager_.current_population() == economy_manager_.total_population())
			{
				return;
			}
			else
			{
				building_manager_.set_building_type(TileType::kStorage);
			}
		};
}

void Game::CreateTextboxes()
{
	const std::string population = std::to_string(economy_manager_.current_population()) + "/" + std::to_string(economy_manager_.total_population());
	const TextBox current_pop(sf::Vector2f(1860, 75), population, 15, sf::Color::Black, true);
	textboxes_[0] = current_pop;
	const TextBox current_food(sf::Vector2f(1860, 98), std::to_string(economy_manager_.food()), 15, sf::Color::Black, true);
	textboxes_[1] = current_food;
	const TextBox current_wood(sf::Vector2f(1860, 119), std::to_string(economy_manager_.wood()), 15, sf::Color::Black, true);
	textboxes_[2] = current_wood;
	const TextBox current_stone(sf::Vector2f(1860, 140), std::to_string(economy_manager_.stone()), 15, sf::Color::Black, true);
	textboxes_[3] = current_stone;

	const TextBox house_cost_1(sf::Vector2f(55, 165), std::to_string(economy_manager_.current_house_cost()), 24, sf::Color::Black, false);
	textboxes_[4] = house_cost_1;
	const TextBox house_cost_2(sf::Vector2f(129, 165), std::to_string(economy_manager_.current_house_cost()), 24, sf::Color::Black, false);
	textboxes_[5] = house_cost_2;
	const TextBox forge_cost_1(sf::Vector2f(55, 220), std::to_string(economy_manager_.current_forge_cost()), 24, sf::Color::Black, false);
	textboxes_[6] = forge_cost_1;
	const TextBox forge_cost_2(sf::Vector2f(129, 220), std::to_string(economy_manager_.current_forge_cost()), 24, sf::Color::Black, false);
	textboxes_[7] = forge_cost_2;
	const TextBox sawmill_cost_1(sf::Vector2f(55, 275), std::to_string(economy_manager_.current_sawmill_cost()), 24, sf::Color::Black, false);
	textboxes_[8] = sawmill_cost_1;
	const TextBox sawmill_cost_2(sf::Vector2f(129, 275), std::to_string(economy_manager_.current_sawmill_cost()), 24, sf::Color::Black, false);
	textboxes_[9] = sawmill_cost_2;
	const TextBox storage_cost_1(sf::Vector2f(55, 330), std::to_string(economy_manager_.current_storage_cost()), 24, sf::Color::Black, false);
	textboxes_[10] = storage_cost_1;
	const TextBox storage_cost_2(sf::Vector2f(129, 330), std::to_string(economy_manager_.current_storage_cost()), 24, sf::Color::Black, false);
	textboxes_[11] = storage_cost_2;
}

void Game::UpdateTextboxes()
{
	const std::string population = std::to_string(economy_manager_.current_population()) + "/" + std::to_string(economy_manager_.total_population());

	textboxes_[0].update_textbox(economy_manager_.current_population() == economy_manager_.total_population() ? sf::Color::Red : sf::Color::Black, population);
	textboxes_[1].update_textbox(sf::Color::Black, std::to_string(economy_manager_.food()));
	textboxes_[2].update_textbox(sf::Color::Black, std::to_string(economy_manager_.wood()));
	textboxes_[3].update_textbox(sf::Color::Black, std::to_string(economy_manager_.stone()));

	//wood - food, wood - stone
	textboxes_[4].update_textbox(economy_manager_.wood() < economy_manager_.current_house_cost() ? sf::Color::Red : sf::Color::Black, std::to_string(economy_manager_.current_house_cost()));
	textboxes_[5].update_textbox(economy_manager_.food() < economy_manager_.current_house_cost() ? sf::Color::Red : sf::Color::Black, std::to_string(economy_manager_.current_house_cost()));
	textboxes_[6].update_textbox(economy_manager_.wood() < economy_manager_.current_forge_cost() ? sf::Color::Red : sf::Color::Black, std::to_string(economy_manager_.current_forge_cost()));
	textboxes_[7].update_textbox(economy_manager_.stone() < economy_manager_.current_forge_cost() ? sf::Color::Red : sf::Color::Black, std::to_string(economy_manager_.current_forge_cost()));
	textboxes_[8].update_textbox(economy_manager_.wood() < economy_manager_.current_sawmill_cost() ? sf::Color::Red : sf::Color::Black, std::to_string(economy_manager_.current_sawmill_cost()));
	textboxes_[9].update_textbox(economy_manager_.stone() < economy_manager_.current_sawmill_cost() ? sf::Color::Red : sf::Color::Black, std::to_string(economy_manager_.current_sawmill_cost()));
	textboxes_[10].update_textbox(economy_manager_.wood() < economy_manager_.current_storage_cost() ? sf::Color::Red : sf::Color::Black, std::to_string(economy_manager_.current_storage_cost()));
	textboxes_[11].update_textbox(economy_manager_.stone() < economy_manager_.current_storage_cost() ? sf::Color::Red : sf::Color::Black, std::to_string(economy_manager_.current_storage_cost()));

	economy_manager_.set_text_to_update(false);
}