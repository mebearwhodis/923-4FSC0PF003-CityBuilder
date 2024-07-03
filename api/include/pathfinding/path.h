#ifndef API_PATHFINDING_PATH_H_
#define API_PATHFINDING_PATH_H_
#include <queue>
#include <SFML/System/Vector2.hpp>

class Path
{
public:
	bool IsEnded();
	bool IsAvailable();
	bool IsReady();

	sf::Vector2f GetNextStep();
	void SetSteps(std::vector<sf::Vector2f> steps);

	// steps getter
	const std::queue<sf::Vector2f>& GetSteps();
private:
	std::queue<sf::Vector2f> steps_;
	sf::Vector2f next_step_;
	bool is_available_ = false;

	//TODO to be changed with job system implementation:
	bool is_ready_ = true;
};

#endif