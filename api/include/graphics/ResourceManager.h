#ifndef API_GRAPHICS_RESOURCEMANAGER_H
#define API_GRAPHICS_RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {

public:
	enum class Resource
	{
		WhiteButtonRedFrame,
		TerrainForest
	};

private:
	std::unordered_map<Resource, sf::Texture> textures_;
	sf::Texture blankTexture_;

	void LoadAllTextures();

public:
	static ResourceManager& Get() {
		static ResourceManager instance_;
		return instance_;
	}


	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	sf::Texture& GetTexture(Resource resourceId);

};

#endif