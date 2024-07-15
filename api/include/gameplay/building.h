#ifndef API_GAMEPLAY_BUILDING_H_
#define API_GAMEPLAY_BUILDING_H_
#include <SFML/Graphics/Sprite.hpp>

#include "../graphics/sprite_entity.h"

class Building : public SpriteEntity
{
public:
	Building(TileType type, float x, float y);

protected:
	virtual void DefineTexture(int type) override;
};
#endif // API_GAMEPLAY_BUILDING_H_
