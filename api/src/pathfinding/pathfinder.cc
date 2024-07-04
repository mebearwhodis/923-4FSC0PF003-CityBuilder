#include "pathfinding/pathfinder.h"

#include <iostream>
#include <unordered_set>

#include "sfml_utils.h"


static std::vector<sf::Vector2f> ConstructPath(const PathPoint& exit_point, const PathPoint* visited_points)
{
	std::vector<sf::Vector2f> positions;

	PathPoint point = exit_point;

	positions.emplace_back(point.position());
	while (point.parent_index() != -1)
	{
		point = visited_points[point.parent_index()];
		positions.push_back(point.position());
	}
	std::ranges::reverse(positions);
	return positions;
}

template<>
struct std::hash<sf::Vector2f>
{
	std::size_t operator()(const sf::Vector2f& v) const noexcept
	{
		std::size_t h1 = std::hash<float>{}(v.x);
		std::size_t h2 = std::hash<float>{}(v.y);
		return h1 ^ (h2 << 1); // or use boost::hash_combine
	}
};

Path Pathfinder::CalculatePath(std::vector<sf::Vector2f> positions, sf::Vector2f start, sf::Vector2f end, int tile_size)
{
	Path path;

	sf::Vector2f rounded_start;
	rounded_start.x = start.x - std::fmod(start.x, static_cast<float>(tile_size));
	rounded_start.y = start.y - std::fmod(start.y, static_cast<float>(tile_size));

	sf::Vector2f rounded_end;
	rounded_end.x = end.x - std::fmod(end.x, static_cast<float>(tile_size));
	rounded_end.y = end.y - std::fmod(end.y, static_cast<float>(tile_size));

	// Set list up with start and end
	positions.emplace_back(rounded_start);
	positions.emplace_back(end);

	// --
	std::priority_queue<PathPoint, std::vector<PathPoint>, std::greater<PathPoint>> open_queue;
	std::unordered_set<sf::Vector2f> open_list;
	std::unordered_set<sf::Vector2f> closed_list;
	std::vector<PathPoint> visited_points;

	open_queue.emplace(0, Magnitude(rounded_end - rounded_start), rounded_start, -1);
	open_list.emplace(rounded_start);

	while(!open_queue.empty())
	{
		// Find lowest score point
		auto current = open_queue.top();
		closed_list.emplace(current.position());

		open_queue.pop();
		std::erase_if(open_list, [&current](sf::Vector2f p) {return current.position() == p; });

		// Did we find the exit of the maze ?
		if (Magnitude(rounded_end - current.position()) <= std::numeric_limits<float>::epsilon())
		{
			path.SetSteps(ConstructPath(current, visited_points.data()));
			std::cout << "Found the path : nb steps = " << path.GetSteps().size() << std::endl;
			return path;
		}

		for (auto neighbour : kNeighbours)
		{
			sf::Vector2f neighbourPos = current.position() + neighbour * static_cast<float>(tile_size);

			// Tous les voisins
			auto found_position = std::find_if(positions.begin(), positions.end(), [&neighbourPos](sf::Vector2f& pos)
				{
					return pos == neighbourPos;
				});

			// Didn't found a valid neighbour
			// Possible cases : outside of the map, empty lists, etc.
			if (found_position != positions.end())
			{
				if(*found_position == current.position())
				{
					std::cerr << "Nope\n";
				}
				bool is_in_closed = closed_list.contains(*found_position);
				bool is_in_open = open_list.contains(*found_position);


				if (!is_in_closed && !is_in_open)
				{
					auto index = visited_points.size();
					visited_points.push_back(current);


					open_queue.emplace(current.g() + tile_size, Magnitude(rounded_end - current.position()), *found_position, index);
					open_list.emplace(*found_position);
				}
			}
		}
	}

	// -
	std::cout << "Didn't find the path" << std::endl;
	std::cout << "Start : " << start.x << " " << start.y << std::endl;
	std::cout << "Rounded Start : " << rounded_start.x << " " << rounded_start.y << std::endl;
	std::cout << "End : " << end.x << " " << end.y << std::endl;
	std::cout << "Rounded end : " << rounded_end.x << " " << rounded_end.y << std::endl;

	return path;


}