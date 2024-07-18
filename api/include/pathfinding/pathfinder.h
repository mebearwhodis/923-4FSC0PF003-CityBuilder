#ifndef API_PATHFINDING_PATHFINDER_
#define API_PATHFINDING_PATHFINDER_
#include <array>

#include "path.h"

//TODO: CLEANUP Comment all of this

class PathPoint
{
	// Members
	float f_;
	// Cost of the cheapest path from start to current PathPoint
	float g_;

	// Heuristic function value (estimated cost to goal)
	float h_;

	sf::Vector2f position_;

	std::uint32_t parent_index_ = -1;

public:
	// Constructors
	PathPoint() = default;
	PathPoint(float g, float h, sf::Vector2f position, std::uint32_t parent_index) : g_(g), h_(h), position_(position), parent_index_(parent_index)
	{
		f_ = g + h;
	}

	// Operators
	bool operator<(const PathPoint& other) const {
		return this->f_ < other.f_;
	}
	bool operator>(const PathPoint& other) const {
		return this->f_ > other.f_;
	}

	// Accessors
	std::uint32_t parent_index() const { return parent_index_; }

	const sf::Vector2f& position() const { return position_; }

	float g() const { return g_; }
};

const std::array kNeighbours = {
sf::Vector2f(0,1),
sf::Vector2f(1,0),
sf::Vector2f(0,-1),
sf::Vector2f(-1,0)
};

//A* pathfinding 

Path CalculatePath(std::vector<sf::Vector2f> positions, sf::Vector2f start, sf::Vector2f end, int tile_size);


#endif