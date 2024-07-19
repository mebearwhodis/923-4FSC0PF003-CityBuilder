#ifndef API_GRAPHICS_RESOURCEMANAGER_H_
#define API_GRAPHICS_RESOURCEMANAGER_H_

#include <array>
#include <SFML/Graphics.hpp>

#include "containers/small_vector.h"
#include "enum.h"

class ResourceManager
{
private:
	std::array<sf::Image, static_cast<int>(CursorType::kLength)> cursor_images_;
	std::array<sf::Texture, static_cast<int>(UiTexture::kLength)> ui_textures_;
	std::array<core::SmallVector<sf::Texture, 4>, static_cast<int>(TileType::kLength)> tile_textures_;
	std::array<core::SmallVector<sf::Texture, 8>, static_cast<int>(VillagerType::kLength)> character_textures_;

	sf::Texture blank_texture_;
	sf::Image blank_cursor_image_;
	sf::Font font_;

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

	sf::Font& font() { return font_; }
	sf::Texture& GetUiTexture(UiTexture resource_id);
	sf::Image& GetCursorImage(CursorType cursor_id);
	const core::SmallVector<sf::Texture, 4>& GetTileTextures(TileType type) const;
	const core::SmallVector<sf::Texture, 8>& GetCharacterTextures(VillagerType type) const;
};
#endif