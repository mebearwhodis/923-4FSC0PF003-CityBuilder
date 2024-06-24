#include "graphics/resource_manager.h"

#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif

void ResourceManager::LoadAllTextures()
{
	#ifdef TRACY_ENABLE
		ZoneScoped;
	#endif
	//TODO use kMax to resize
	// Textures -----------------
	blankTexture_ = sf::Texture();
	textures_[Resource::kWhiteButtonRedFrame].loadFromFile("../resources/sprites/ui/red_button10.png");
	textures_[Resource::kTerrainForest].loadFromFile("../resources/sprites/tiles/medievalTile_48.png");
	textures_[Resource::kTerrainForestCutDown].loadFromFile("../resources/sprites/tiles/medievalTile_52.png");
	textures_[Resource::kHouse].loadFromFile("../resources/sprites/tiles/medievalStructure_17.png");

}

ResourceManager::ResourceManager()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	LoadAllTextures();
}

sf::Texture& ResourceManager::GetTexture(Resource resourceId) {

#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	if (textures_.contains(resourceId)) {
		return textures_.at(resourceId);
	}
	else
	{
		return blankTexture_;
	}
	//if(static_cast<int>(resourceId) < )


}