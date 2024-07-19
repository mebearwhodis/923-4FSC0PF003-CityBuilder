#ifndef API_PATHFINDING_PATH_H_
#define API_PATHFINDING_PATH_H_

#include <queue>
#include <SFML/System/Vector2.hpp>

class Path
{
private:
	std::queue<sf::Vector2f> steps_;
	sf::Vector2f next_step_;
	sf::Vector2f final_destination_;
	bool is_available_ = false;
	bool is_ready_ = true;

public:
	sf::Vector2f GetNextStep();
	const std::queue<sf::Vector2f>& GetSteps();
	void SetSteps(std::vector<sf::Vector2f> steps);

	[[nodiscard]] sf::Vector2f final_destination() const;
	[[nodiscard]] bool is_available() const;
	[[nodiscard]] bool is_ended() const;
	[[nodiscard]] bool is_ready() const;

	void set_is_available(const bool value) { is_available_ = value; }
	void set_is_ready(const bool value) { is_ready_ = value; }
};

#endif