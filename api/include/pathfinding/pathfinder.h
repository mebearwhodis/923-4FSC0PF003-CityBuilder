#ifndef API_PATHFINDING_PATHFINDER_
#define API_PATHFINDING_PATHFINDER_
#include <array>

#include "path.h"

struct PathPoint
{
	// Members
	float g;
	float h;

	sf::Vector2f position;

	PathPoint* parent = nullptr;

	// Constructor
	PathPoint(float g, float h, sf::Vector2f position, PathPoint* parent) : g(g), h(h), position(position), parent(parent) {}


	// Methods
	int f() const { return g + h; }	// Total cost


	// Operators
	bool operator>(const PathPoint& other) const
	{
		return f() > other.f();
	}
};

const std::array kNeighbours = {
sf::Vector2f(0,1),
sf::Vector2f(1,0),
sf::Vector2f(0,-1),
sf::Vector2f(-1,0)
};

class Pathfinder
{
	std::vector<sf::Vector2f> ConstructPath(PathPoint exit_point);
public:
	Path CalculatePath(std::vector<sf::Vector2f> positions, sf::Vector2f start, sf::Vector2f end, int tile_size);
};

#endif