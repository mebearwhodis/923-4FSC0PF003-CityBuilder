#ifndef API_GAMEPLAY_BUILDING_H_
#define API_GAMEPLAY_BUILDING_H_
#include <SFML/Graphics/Sprite.hpp>


//TODO: class Building with enum of BuildingType
//Sprite, BuildingType, Cost, State
//More specific building classes could inherit from it (Building->House/Sawmill/Forge/etc. could inherit and add specific function)


class Building : public sf::Drawable
{
public:
	Building(float x, float y);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite sprite_;
};
#endif // API_GAMEPLAY_BUILDING_H_
