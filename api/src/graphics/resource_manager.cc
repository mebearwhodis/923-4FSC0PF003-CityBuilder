#include "graphics/resource_manager.h"

void ResourceManager::LoadAllTextures()
{
	// Ui Textures -----------------
	blank_texture_ = sf::Texture();
	ui_textures_.at(static_cast<int>(UiTexture::kWhiteButtonRedFrame)).loadFromFile("../resources/sprites/ui/red_button10.png");

	// Tile Textures -----------------
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_57.png", TileType::kPlain);
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_58.png", TileType::kPlain);

	//LoadTileTexture("../resources/sprites/tiles/medievalTile_41.png", TileType::kForest);
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_42.png", TileType::kForest);
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_43.png", TileType::kForest);
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_44.png", TileType::kForest);
	//
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_45.png", TileType::kPineForest);
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_46.png", TileType::kPineForest);
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_47.png", TileType::kPineForest);
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_48.png", TileType::kPineForest);

	//LoadTileTexture("../resources/sprites/tiles/medievalTile_49.png", TileType::kForestCutDown);
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_50.png", TileType::kForestCutDown);
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_51.png", TileType::kForestCutDown);
	//LoadTileTexture("../resources/sprites/tiles/medievalTile_52.png", TileType::kForestCutDown);

	//LoadTileTexture("../resources/sprites/structures/medievalStructure_09.png", TileType::kHouse);
	//LoadTileTexture("../resources/sprites/structures/medievalStructure_16.png", TileType::kHouse);
	//LoadTileTexture("../resources/sprites/structures/medievalStructure_17.png", TileType::kHouse);
	//LoadTileTexture("../resources/sprites/structures/medievalStructure_18.png", TileType::kHouse);

	LoadTileTexture("../resources/sprites/new_tiles/grass_centre.png", TileType::grass_centre);
	LoadTileTexture("../resources/sprites/new_tiles/grass_U.png", TileType::grass_U);
	LoadTileTexture("../resources/sprites/new_tiles/grass_UR.png", TileType::grass_UR);
	LoadTileTexture("../resources/sprites/new_tiles/grass_R.png", TileType::grass_R);
	LoadTileTexture("../resources/sprites/new_tiles/grass_DR.png", TileType::grass_DR);
	LoadTileTexture("../resources/sprites/new_tiles/grass_D.png", TileType::grass_D);
	LoadTileTexture("../resources/sprites/new_tiles/grass_DL.png", TileType::grass_DL);
	LoadTileTexture("../resources/sprites/new_tiles/grass_L.png", TileType::grass_L);
	LoadTileTexture("../resources/sprites/new_tiles/grass_UL.png", TileType::grass_UL);

	LoadTileTexture("../resources/sprites/new_tiles/grass_groundUR.png", TileType::grass_groundUR);
	LoadTileTexture("../resources/sprites/new_tiles/grass_groundDR.png", TileType::grass_groundDR);
	LoadTileTexture("../resources/sprites/new_tiles/grass_groundDL.png", TileType::grass_groundDL);
	LoadTileTexture("../resources/sprites/new_tiles/grass_groundUL.png", TileType::grass_groundUL);

	LoadTileTexture("../resources/sprites/new_tiles/grass_waterUR.png", TileType::grass_waterUR);
	LoadTileTexture("../resources/sprites/new_tiles/grass_waterDR.png", TileType::grass_waterDR);
	LoadTileTexture("../resources/sprites/new_tiles/grass_waterDL.png", TileType::grass_waterDL);
	LoadTileTexture("../resources/sprites/new_tiles/grass_waterUL.png", TileType::grass_waterUL);

	LoadTileTexture("../resources/sprites/new_tiles/ground_centre.png", TileType::ground_centre);
	LoadTileTexture("../resources/sprites/new_tiles/ground_U.png", TileType::ground_U);
	LoadTileTexture("../resources/sprites/new_tiles/ground_UR.png", TileType::ground_UR);
	LoadTileTexture("../resources/sprites/new_tiles/ground_R.png", TileType::ground_R);
	LoadTileTexture("../resources/sprites/new_tiles/ground_DR.png", TileType::ground_DR);
	LoadTileTexture("../resources/sprites/new_tiles/ground_D.png", TileType::ground_D);
	LoadTileTexture("../resources/sprites/new_tiles/ground_DL.png", TileType::ground_DL);
	LoadTileTexture("../resources/sprites/new_tiles/ground_L.png", TileType::ground_L);
	LoadTileTexture("../resources/sprites/new_tiles/ground_UL.png", TileType::ground_UL);

	LoadTileTexture("../resources/sprites/new_tiles/ground_grassU.png", TileType::ground_grassU);
	LoadTileTexture("../resources/sprites/new_tiles/ground_grassUR.png", TileType::ground_grassUR);
	LoadTileTexture("../resources/sprites/new_tiles/ground_grassR.png", TileType::ground_grassR);
	LoadTileTexture("../resources/sprites/new_tiles/ground_grassDR.png", TileType::ground_grassDR);
	LoadTileTexture("../resources/sprites/new_tiles/ground_grassD.png", TileType::ground_grassD);
	LoadTileTexture("../resources/sprites/new_tiles/ground_grassDL.png", TileType::ground_grassDL);
	LoadTileTexture("../resources/sprites/new_tiles/ground_grassL.png", TileType::ground_grassL);
	LoadTileTexture("../resources/sprites/new_tiles/ground_grassUL.png", TileType::ground_grassUL);

	LoadTileTexture("../resources/sprites/new_tiles/ground_waterUR.png", TileType::ground_waterUR);
	LoadTileTexture("../resources/sprites/new_tiles/ground_waterDR.png", TileType::ground_waterDR);
	LoadTileTexture("../resources/sprites/new_tiles/ground_waterDL.png", TileType::ground_waterDL);
	LoadTileTexture("../resources/sprites/new_tiles/ground_waterUL.png", TileType::ground_waterUL);

	LoadTileTexture("../resources/sprites/new_tiles/water01.png", TileType::water01);




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

void ResourceManager::LoadTileTexture(const std::string& filepath, TileType type)
{
	sf::Texture texture;
	if(texture.loadFromFile(filepath))
	{
		tile_textures_[type].push_back(texture);
	}
}

void ResourceManager::LoadCharacterTexture(const std::string& filepath, VillagerType type)
{
	sf::Texture texture;
	if (texture.loadFromFile(filepath))
	{
		character_textures_[type].push_back(texture);
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