#ifndef API_GRAPHICS_RESOURCEMANAGER_H_
#define API_GRAPHICS_RESOURCEMANAGER_H_

#include <array>
#include <SFML/Graphics.hpp>
#include "../enum.h"
#include "containers/small_vector.h"

class ResourceManager {

private:
	std::array<sf::Texture, static_cast<int>(UiTexture::kLength)> ui_textures_;
	std::array<sf::Image, static_cast<int>(CursorType::kLength)> cursor_images_;

	std::array<core::SmallVector<sf::Texture, 4>, static_cast<int>(TileType::kLength)> tile_textures_;
	std::array<core::SmallVector<sf::Texture, 8>, static_cast<int>(VillagerType::kLength)> character_textures_;

	sf::Texture blank_texture_;
	sf::Image blank_cursor_image_;

	void LoadAllTextures();
	void LoadUITexture(const std::string& filepath, UiTexture ui_texture);
	void LoadTileTexture(const std::string& filepath, TileType type);
	void LoadCharacterTexture(const std::string& filepath, VillagerType type);

public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager& Get();

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	//TODO rename getters
	sf::Texture& GetUiTexture(UiTexture resource_id);
	sf::Image& GetCursorImage(CursorType cursor_id);
	const core::SmallVector<sf::Texture, 4>& GetTileTextures(TileType type) const {
		return tile_textures_[(static_cast<int>(type))];}
	const core::SmallVector<sf::Texture, 8>& GetCharacterTextures(VillagerType type) const
	{
		return character_textures_[(static_cast<int>(type))];
	}
};

#endif