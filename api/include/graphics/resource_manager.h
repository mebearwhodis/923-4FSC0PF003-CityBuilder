#ifndef API_GRAPHICS_RESOURCEMANAGER_H_
#define API_GRAPHICS_RESOURCEMANAGER_H_

#include <array>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "../enum.h"

class ResourceManager {

	//TODO: have multiple enums for terrain/UI/...? -> multiple "GetTexture", one for each?
public:


private:
	//TODO make one for each type of resource and change for array, using kLength for size
	std::array<sf::Texture, static_cast<int>(Resource::kLength)> textures_;
	std::array<sf::Image, static_cast<int>(CursorType::kLength)> cursor_images_;

	sf::Texture blank_texture_;
	sf::Image blank_cursor_image_;

	ResourceManager();
	void LoadAllTextures();

public:
	static ResourceManager& Get();

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	sf::Texture& GetTexture(Resource resource_id);
	sf::Image& GetCursorImage(CursorType cursor_id);

};

#endif