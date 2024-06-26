#ifndef API_GRAPHICS_SPRITE_ENTITY_H_
#define API_GRAPHICS_SPRITE_ENTITY_H_
#include <SFML/Graphics/Sprite.hpp>
#include "../graphics/resource_manager.h"
#include "../enum.h"

class SpriteEntity : public sf::Drawable
{
public:
	SpriteEntity(float x, float y);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void DefineTexture() = 0;
	sf::Sprite sprite_;
};
#endif // API_GRAPHICS_SPRITE_ENTITY_H_
