#include <pathfinding/path.h>

bool Path::is_ended() const
{
	return steps_.empty();
}

bool Path::is_available() const
{
	return is_available_;
}

bool Path::is_ready() const
{
	return is_ready_;
}

sf::Vector2f Path::GetNextStep()
{
	if(!steps_.empty())
	{
		next_step_ = steps_.front();
		steps_.pop();
	}
	return next_step_;
}

void Path::SetSteps(std::vector<sf::Vector2f> steps)
{
	if(!steps.empty())
	{
		steps_ = std::queue<sf::Vector2f>();
		for (auto step : steps)
		{
			steps_.push(step);
		}

		is_available_ = true;
	}else
	{
		is_available_ = false;
	}
}

const std::queue<sf::Vector2f>& Path::GetSteps()
{
	return steps_;
}
