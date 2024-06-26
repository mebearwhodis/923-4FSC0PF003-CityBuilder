#ifndef API_GAMEPLAY_BUILDING_H_
#define API_GAMEPLAY_BUILDING_H_
#include <SFML/Graphics/Sprite.hpp>

#include "../graphics/sprite_entity.h"


//TODO: class Building with enum of BuildingType, will have the Update/Tick function?
//Sprite, BuildingType, Cost, State
//More specific building classes could inherit from it (Building->House/Sawmill/Forge/etc. could inherit and add specific function)


class Building : public SpriteEntity
{
public:
	Building(float x, float y);

protected:
	virtual void DefineTexture() override;
};
#endif // API_GAMEPLAY_BUILDING_H_
