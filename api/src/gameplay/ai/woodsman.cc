#include "gameplay/ai/woodsman.h"

#include <SFML/Graphics/Texture.hpp>


Woodsman::Woodsman(float x, float y, float linear_speed): Walker(x, y, linear_speed)
{
	DefineTexture();
}

//sprite_.setPosition(x, y);
void Woodsman::DefineTexture()
{
	const auto& textures = ResourceManager::Get().GetCharacterTextures(VillagerType::kVillager);
	if (!textures.empty()) {
		const sf::Texture& texture = textures[std::rand() % textures.size()];
		sprite_.setTexture(texture);
	}
}
