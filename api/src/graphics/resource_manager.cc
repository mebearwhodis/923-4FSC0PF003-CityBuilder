#include "graphics/resource_manager.h"
#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#include <Tracy/TracyC.h>
#endif

void ResourceManager::LoadAllTextures()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif


#ifdef TRACY_ENABLE
	TracyCZoneN(blankTexture, "Blank Texture", true);
#endif
	// Ui Textures -----------------
	blank_texture_ = sf::Texture();
#ifdef TRACY_ENABLE
	TracyCZoneEnd(blankTexture);

#endif

#ifdef TRACY_ENABLE
	TracyCZoneN(buttonTexture, "Button Texture", true);
#endif

	//ui_textures_.at(static_cast<int>(UiTexture::kWhiteButtonRedFrame)).loadFromFile("../resources/sprites/ui/red_button10.png");
	LoadUITexture();
#ifdef TRACY_ENABLE
	TracyCZoneEnd(buttonTexture);
#endif



	// Tile Textures -----------------
	LoadTileTexture("../resources/sprites/tiles/medievalTile_57.png", TileType::kPlain);
	LoadTileTexture("../resources/sprites/tiles/medievalTile_58.png", TileType::kPlain);

	LoadTileTexture("../resources/sprites/tiles/medievalTile_41.png", TileType::kForest);
	LoadTileTexture("../resources/sprites/tiles/medievalTile_42.png", TileType::kForest);
	LoadTileTexture("../resources/sprites/tiles/medievalTile_43.png", TileType::kForest);
	LoadTileTexture("../resources/sprites/tiles/medievalTile_44.png", TileType::kForest);

	LoadTileTexture("../resources/sprites/tiles/medievalTile_45.png", TileType::kPineForest);
	LoadTileTexture("../resources/sprites/tiles/medievalTile_46.png", TileType::kPineForest);
	LoadTileTexture("../resources/sprites/tiles/medievalTile_47.png", TileType::kPineForest);
	LoadTileTexture("../resources/sprites/tiles/medievalTile_48.png", TileType::kPineForest);

	LoadTileTexture("../resources/sprites/tiles/medievalTile_49.png", TileType::kForestCutDown);
	LoadTileTexture("../resources/sprites/tiles/medievalTile_50.png", TileType::kForestCutDown);
	LoadTileTexture("../resources/sprites/tiles/medievalTile_51.png", TileType::kForestCutDown);
	LoadTileTexture("../resources/sprites/tiles/medievalTile_52.png", TileType::kForestCutDown);

	LoadTileTexture("../resources/sprites/structures/medievalStructure_09.png", TileType::kHouse);
	LoadTileTexture("../resources/sprites/structures/medievalStructure_16.png", TileType::kHouse);
	LoadTileTexture("../resources/sprites/structures/medievalStructure_17.png", TileType::kHouse);
	LoadTileTexture("../resources/sprites/structures/medievalStructure_18.png", TileType::kHouse);


	// Character Textures -----------------
	LoadCharacterTexture("../resources/sprites/units/medievalUnit_05.png", VillagerType::kVillager);
	LoadCharacterTexture("../resources/sprites/units/medievalUnit_06.png", VillagerType::kVillager);
	LoadCharacterTexture("../resources/sprites/units/medievalUnit_11.png", VillagerType::kVillager);
	LoadCharacterTexture("../resources/sprites/units/medievalUnit_12.png", VillagerType::kVillager);
	LoadCharacterTexture("../resources/sprites/units/medievalUnit_17.png", VillagerType::kVillager);
	LoadCharacterTexture("../resources/sprites/units/medievalUnit_18.png", VillagerType::kVillager);
	LoadCharacterTexture("../resources/sprites/units/medievalUnit_23.png", VillagerType::kVillager);
	LoadCharacterTexture("../resources/sprites/units/medievalUnit_24.png", VillagerType::kVillager);

	// Cursor Images -----------------
	blank_cursor_image_ = sf::Image();
	cursor_images_[static_cast<int>(CursorType::kBasic)].loadFromFile("../resources/sprites/ui/cursorSword_silver.png");
	cursor_images_[static_cast<int>(CursorType::kGauntlet)].loadFromFile("../resources/sprites/ui/cursorGauntlet_blue.png");

}

void ResourceManager::LoadUITexture()
{
#ifdef TRACY_ENABLE
	TracyCZoneN(loadUIImage, "Load UI image", true);
#endif
	//---- Things to measure
	sf::Image image;
	if (!image.loadFromFile("../resources/sprites/ui/red_button10.png"))
	{
		return;
	}
#ifdef TRACY_ENABLE
	TracyCZoneEnd(loadUIImage);
#endif


#ifdef TRACY_ENABLE
	TracyCZoneN(loadUITexture, "Load UI texture", true);
#endif
	sf::Texture texture;
	if (texture.loadFromImage(image))
	{
		ui_textures_.at(static_cast<int>(UiTexture::kWhiteButtonRedFrame)) = texture;
	}

#ifdef TRACY_ENABLE
	TracyCZoneEnd(loadUITexture);
#endif
}

void ResourceManager::LoadTileTexture(const std::string& filepath, TileType type)
{

#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	//sf::Texture texture;
	//if(texture.loadFromFile(filepath))
	//{
	//	tile_textures_[type].push_back(texture);
	//}

	#ifdef TRACY_ENABLE
	TracyCZoneN(loadImage, "Load image", true);
#endif
	//---- Things to measure
	sf::Image image;
	if (!image.loadFromFile(filepath)) 
	{
		return;
	}
#ifdef TRACY_ENABLE
	TracyCZoneEnd(loadImage);
#endif


#ifdef TRACY_ENABLE
	TracyCZoneN(loadTexture, "Load texture", true);
#endif
	sf::Texture texture;
	if (!texture.loadFromImage(image))
	{
		return;
	}

#ifdef TRACY_ENABLE
	TracyCZoneEnd(loadTexture);
#endif

#ifdef TRACY_ENABLE
	TracyCZoneN(pushbackTexture, "Push texture back", true);
#endif
	tile_textures_[static_cast<int>(type)].PushBack({});
	tile_textures_[static_cast<int>(type)].Back().swap(texture);
#ifdef TRACY_ENABLE
	TracyCZoneEnd(pushbackTexture);
#endif
}

void ResourceManager::LoadCharacterTexture(const std::string& filepath, VillagerType type)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	sf::Texture texture;
	if (texture.loadFromFile(filepath))
	{
		character_textures_[type].push_back(texture);
	}
}

static ResourceManager* instance = nullptr;
ResourceManager::ResourceManager()
{
	instance = this;
	LoadAllTextures();
}

ResourceManager::~ResourceManager()
{
	instance = nullptr;
}

ResourceManager& ResourceManager::Get()
{
	return *instance;
}

sf::Texture& ResourceManager::GetUiTexture(UiTexture resource_id) {
	if (static_cast<int>(resource_id) < ui_textures_.size()) 
	{
		return ui_textures_.at(static_cast<int>(resource_id));
	}
	else
	{
		return blank_texture_;
	}
}

sf::Image& ResourceManager::GetCursorImage(CursorType cursor_id)
{
	if (static_cast<int>(cursor_id) < cursor_images_.size())
	{
		return cursor_images_[static_cast<int>(cursor_id)];
	}
	else
	{
		return blank_cursor_image_;
	}
}