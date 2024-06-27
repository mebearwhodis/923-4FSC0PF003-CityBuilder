#include "pathfinding/pathfinder.h"

#include "sfml_utils.h"


std::vector<sf::Vector2f> Pathfinder::ConstructPath(PathPoint exit_point)
{
	std::vector<sf::Vector2f> positions;

	PathPoint point = exit_point;

	positions.emplace_back(point.position);
	while (point.parent != nullptr)
	{
		point = *point.parent;
		positions.insert(positions.begin(), point.position);
	}

	return positions;
}

Path Pathfinder::CalculatePath(std::vector<sf::Vector2f> positions, sf::Vector2f start, sf::Vector2f end, int tile_size)
{
	Path path;

	// Set list up with start and end
	positions.emplace_back(start);
	positions.emplace_back(end);

	//A*
	std::priority_queue<PathPoint, std::vector<PathPoint>, std::greater<>> opened;
	std::vector<PathPoint*> closed;

	opened.emplace(0, Magnitude(end - start), start, nullptr);

	while(!opened.empty())
	{
		// Find lowest score point
		PathPoint current = opened.top();
		opened.pop();

		closed.emplace_back(&current);

		// Did we find the exit of the maze?
		if(current.position == end)
		{
			path.SetSteps(ConstructPath(current));
			return path;
		}
		for (auto neighbour : kNeighbours)
		{
			sf::Vector2f neighbourPos = current.position + sf::Vector2f(neighbour.x * tile_size, neighbour.y * tile_size);
			auto found = std::find_if(positions.begin(), positions.end(), [&neighbourPos](sf::Vector2f& pos)
				{
					return (pos.x == neighbourPos.x) && (pos.y == neighbourPos.y);
				});

			//No valid neighbour found
			if(found != positions.end())
			{
				auto closed_found = std::find_if(
					closed.begin(),
					closed.end(),
					[&found](PathPoint* closed) {return closed->position == *found; }
				);
				if(closed_found == closed.end())
				{
					opened.emplace(current.g + tile_size, Magnitude(end - current.position), *found, &current);
				}
			}
		}
	}
	return path;
}
