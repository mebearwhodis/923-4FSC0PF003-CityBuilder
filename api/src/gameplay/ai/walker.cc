
#include "gameplay/ai/walker.h"

#include <iostream>

#include "utils.h"
#include "behaviour_tree/node.h"
#include "pathfinding/pathfinder.h"


Walker::Walker(float x, float y, float linear_speed) : SpriteEntity(x, y)
{
	setPosition(x, y);
	destination_ = getPosition();
	linear_speed_ = linear_speed;
	last_time_ = std::chrono::steady_clock::now();
}

void Walker::set_destination(sf::Vector2f destination)
{
	destination_ = destination;
}
void Walker::set_destination(float x, float y)
{
	set_destination(sf::Vector2f(x, y));
}

void Walker::set_linear_speed(float linear_speed)
{
	linear_speed_ = linear_speed;
}

void Walker::set_path(const Path& path)
{
	
	if(path.is_available() && path.is_ready())
	{
		path_ = path;
	}
}

void Walker::Tick()
{
	const auto now = std::chrono::steady_clock::now();
	const std::chrono::duration<float> elapsed_time = now - last_time_;
	last_time_ = now;
	const auto delta_time = elapsed_time.count();

	if (path_.is_available()) {
		const sf::Vector2f actual_position = getPosition();
		const sf::Vector2f direction = Normalized(destination_ - actual_position);
		sf::Vector2f new_position;

		if (Magnitude(destination_ - actual_position) < 16.0f) {
			new_position = destination_;
			destination_ = path_.GetNextStep();
		}
		else {
			new_position = actual_position + direction * delta_time * linear_speed_;
		}
		setPosition(new_position);
		sprite_.setPosition(new_position); // Use new_position directly
		frame_.setPosition(new_position);
	}
}

sf::Vector2f Walker::GetLastDestination() const
{
	return destination_;
}

behaviour_tree::Status Walker::GoToNearest(Tilemap& tilemap, sf::Vector2f pos, int& stamina, bool use_stamina) {
	if (squaredMagnitude(pos - path_.final_destination()) > std::numeric_limits<float>::epsilon()) {
		Path p = CalculatePath(tilemap.GetWalkableTiles(), GetLastDestination(), pos, 64);
		if (p.is_available()) {
			set_path(p);
			if (use_stamina) {
				stamina -= p.GetSteps().size();
			}
		}
		else {
			return behaviour_tree::Status::kFailure;
		}
	}

	return squaredMagnitude(getPosition() - path_.final_destination()) > std::numeric_limits<float>::epsilon() ? behaviour_tree::Status::kRunning : behaviour_tree::Status::kSuccess;
}

