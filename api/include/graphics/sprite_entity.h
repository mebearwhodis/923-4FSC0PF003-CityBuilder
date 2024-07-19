#ifndef API_GRAPHICS_SPRITE_ENTITY_H_
#define API_GRAPHICS_SPRITE_ENTITY_H_

#include <SFML/Graphics/Sprite.hpp>
#include "graphics/resource_manager.h"

class SpriteEntity : public sf::Drawable
{
protected:
	sf::Sprite sprite_;
	sf::RectangleShape frame_;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void DefineTexture(int type) = 0;

public:
	SpriteEntity(float x, float y);
};
#endif // API_GRAPHICS_SPRITE_ENTITY_H_
