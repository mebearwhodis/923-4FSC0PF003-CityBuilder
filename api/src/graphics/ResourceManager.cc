#include "graphics/ResourceManager.h"

void ResourceManager::LoadAllTextures()
{
    // Textures -----------------
    blankTexture_ = sf::Texture();
    textures_[Resource::WhiteButtonRedFrame].loadFromFile("../resources/sprites/ui/red_button10.png");
    textures_[Resource::TerrainForest].loadFromFile("../resources/sprites/tiles/medievalTile_48.png");

}

ResourceManager::ResourceManager()
{
    LoadAllTextures();
}

sf::Texture& ResourceManager::GetTexture(Resource resourceId) {

    if (textures_.contains(resourceId)) {
        return textures_.at(resourceId);
    }
    else
    {
        return blankTexture_;
    }



}