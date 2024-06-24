#ifndef API_GAMEPLAY_AI_WALKER_H_
#define API_GAMEPLAY_AI_WALKER_H_
#include <SFML/Graphics/Transformable.hpp>

class Walker : sf::Transformable
{
	//Pseudocode, in the .cc
	void Tick()
	{
		sf::Vector2f newPosition;
		//Calculate new position
		setPosition(newPosition);
	}
};
#endif // API_GAMEPLAY_AI_WALKER_H_
