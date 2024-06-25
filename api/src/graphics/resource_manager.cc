#include "graphics/resource_manager.h"

void ResourceManager::LoadAllTextures()
{
	// Ui Textures -----------------
	blank_texture_ = sf::Texture();
	ui_textures_.at(static_cast<int>(UiTexture::kWhiteButtonRedFrame)).loadFromFile("../resources/sprites/ui/red_button10.png");

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


	// Cursor Images -----------------
	blank_cursor_image_ = sf::Image();
	cursor_images_[static_cast<int>(CursorType::kBasic)].loadFromFile("../resources/sprites/ui/cursorSword_silver.png");
	cursor_images_[static_cast<int>(CursorType::kGauntlet)].loadFromFile("../resources/sprites/ui/cursorGauntlet_blue.png");

}

void ResourceManager::LoadTileTexture(const std::string& filepath, TileType type)
{
	sf::Texture texture;
	if(texture.loadFromFile(filepath))
	{
		tile_textures_[type].push_back(texture);
	}
}

ResourceManager::ResourceManager()
{
	LoadAllTextures();
}

ResourceManager& ResourceManager::Get()
{
	static ResourceManager instance_;
	return instance_;
}

sf::Texture& ResourceManager::GetUiTexture(UiTexture resource_id) {
	if (static_cast<int>(resource_id) < ui_textures_.size()) {
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