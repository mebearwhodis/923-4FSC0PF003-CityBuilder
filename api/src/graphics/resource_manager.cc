#include "graphics/resource_manager.h"

void ResourceManager::LoadAllTextures()
{
	// Textures -----------------
	blank_texture_ = sf::Texture();
	textures_.at(static_cast<int>(Resource::kWhiteButtonRedFrame)).loadFromFile("../resources/sprites/ui/red_button10.png");
	textures_.at(static_cast<int>(Resource::kTerrainForest)).loadFromFile("../resources/sprites/tiles/medievalTile_48.png");
	textures_.at(static_cast<int>(Resource::kTerrainForestCutDown)).loadFromFile("../resources/sprites/tiles/medievalTile_52.png");

	blank_cursor_image_ = sf::Image();
	cursor_images_[static_cast<int>(CursorType::kBasic)].loadFromFile("../resources/sprites/ui/cursorSword_silver.png");
	cursor_images_[static_cast<int>(CursorType::kGauntlet)].loadFromFile("../resources/sprites/ui/cursorGauntlet_blue.png");

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

sf::Texture& ResourceManager::GetTexture(Resource resource_id) {
	if (static_cast<int>(resource_id) < textures_.size()) {
		return textures_.at(static_cast<int>(resource_id));
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