#ifndef API_GRAPHICS_RESOURCEMANAGER_H_
#define API_GRAPHICS_RESOURCEMANAGER_H_

#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourceManager {

	//TODO: have multiple enums for terrain/UI/...? -> multiple "GetTexture", one for each? Maybe a bad idea
public:
	enum class Resource
	{
		kWhiteButtonRedFrame,
		kTerrainForest,
		kTerrainForestCutDown,
		kHouse,
		//...
		kMax // Last valule, used to get size of the enum
	};

private:
	//TODO was changed to vector, check repo
	std::unordered_map<Resource, sf::Texture> textures_;
	sf::Texture blankTexture_;


	ResourceManager();
	void LoadAllTextures();

public:
	static ResourceManager& Get() {
		static ResourceManager instance_;
		return instance_;
	}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	sf::Texture& GetTexture(Resource resourceId);

};

#endif