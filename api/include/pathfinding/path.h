#ifndef API_PATHFINDING_PATH_H_
#define API_PATHFINDING_PATH_H_
#include <queue>
#include <SFML/System/Vector2.hpp>

class Path
{
public:
	bool is_ended();
	bool is_available();
	bool is_ready();

	sf::Vector2f GetNextStep();
	void SetSteps(std::vector<sf::Vector2f> steps);

	// steps getter
	const std::queue<sf::Vector2f>& GetSteps();

	void set_is_available(bool value) { is_available_ = value; }
	void set_is_ready(bool value) { is_ready_ = value; }
private:
	std::queue<sf::Vector2f> steps_;
	sf::Vector2f next_step_;
	bool is_available_ = false;

	//TODO to be changed with job system implementation:
	bool is_ready_ = false;
};

#endif