#ifndef API_PATHFINDING_PATHFINDER_
#define API_PATHFINDING_PATHFINDER_
#include <array>

#include "path.h"

//TODO Comment all of this, maybe refactor in its own PathPoint class files
class PathPoint
{
	// Members
	float f;
	// Cost of the cheapest path from start to current PathPoint
	float g_;

	// Heuristic function value (estimated cost to goal)
	float h_;

	sf::Vector2f position_;

	PathPoint* parent_ = nullptr;


public:
	// Constructors
	PathPoint() = default;
	PathPoint(float g, float h, sf::Vector2f position, const PathPoint& parent) : g_(g), h_(h), position_(position)
	{
		this->parent_ = new PathPoint(parent);
		f = g + h;
	}
	PathPoint(float g, float h, sf::Vector2f position) : g_(g), h_(h), position_(position)
	{
		this->parent_ = nullptr;
		f = g + h;
	}

	// Operators
	bool operator<(const PathPoint& other) const {
		return this->f < other.f;
	}
	bool operator>(const PathPoint& other) const {
		return this->f > other.f;
	}

	// Accessors
	const PathPoint* parent() const { return parent_; }

	const sf::Vector2f& position() const { return position_; }

	float g() const { return g_; }
};

const std::array kNeighbours = {
sf::Vector2f(0,1),
sf::Vector2f(1,0),
sf::Vector2f(0,-1),
sf::Vector2f(-1,0)
};

//A* pathfinding TODO: Get rid of namespace
namespace Pathfinder
{
	Path CalculatePath(std::vector<sf::Vector2f> positions, sf::Vector2f start, sf::Vector2f end, int tile_size);
};

#endif