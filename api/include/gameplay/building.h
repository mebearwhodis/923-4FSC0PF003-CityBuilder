#ifndef API_GAMEPLAY_BUILDING_H_
#define API_GAMEPLAY_BUILDING_H_
#include <nlohmann/json.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../graphics/sprite_entity.h"

class Building : public SpriteEntity
{
public:
	Building(TileType type, float x, float y);
	TileType type() const { return type_; }
	sf::Vector2f Position() const { return sprite_.getPosition(); }

protected:
	virtual void DefineTexture(int type) override;
	TileType type_;
};
#endif // API_GAMEPLAY_BUILDING_H_
