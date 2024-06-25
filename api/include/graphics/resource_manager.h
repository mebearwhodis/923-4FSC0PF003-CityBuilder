#ifndef API_GRAPHICS_RESOURCEMANAGER_H_
#define API_GRAPHICS_RESOURCEMANAGER_H_

#include <array>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "../enum.h"

class ResourceManager {

private:
	//TODO: have multiple enums for terrain/UI/...? -> multiple "GetTexture", one for each?
	//TODO make one for each type of resource and change for array, using kLength for size
	std::array<sf::Texture, static_cast<int>(UiTexture::kLength)> ui_textures_;
	std::array<sf::Image, static_cast<int>(CursorType::kLength)> cursor_images_;
	std::unordered_map<TileType, std::vector<sf::Texture>> tile_textures_;

	sf::Texture blank_texture_;
	sf::Image blank_cursor_image_;

	ResourceManager();
	void LoadAllTextures();
	void LoadTileTexture(const std::string& filepath, TileType type);

public:
	static ResourceManager& Get();

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	//TODO rename getters
	sf::Texture& GetUiTexture(UiTexture resource_id);
	sf::Image& GetCursorImage(CursorType cursor_id);
	const std::vector<sf::Texture>& GetTileTextures(TileType type) const {
		return tile_textures_.at(type);
	}

};

#endif