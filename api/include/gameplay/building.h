#ifndef API_GAMEPLAY_BUILDING_H_
#define API_GAMEPLAY_BUILDING_H_

#include <SFML/Graphics/Sprite.hpp>

#include "graphics/sprite_entity.h"

class Building : public SpriteEntity
{
protected:
	virtual void DefineTexture(int type) override;
	TileType type_;

public:
	Building(TileType type, float x, float y);

	sf::Vector2f Position() const { return sprite_.getPosition(); }

	TileType type() const { return type_; }
};
#endif // API_GAMEPLAY_BUILDING_H_
