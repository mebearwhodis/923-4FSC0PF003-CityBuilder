
#include "gameplay/ai/walker.h"

#include <iostream>

#include "sfml_utils.h"


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
	destination_.x = x;
	destination_.y = y;
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

	//TODO Factorize DeltaTime -----------
	const auto now{ std::chrono::steady_clock::now() };
	const std::chrono::duration<float> elapsed_time{ now - last_time_ };
	last_time_ = std::chrono::steady_clock::now();
	const auto delta_time = elapsed_time.count();

	if (path_.is_ended())
	{
		//std::cout << "Path finished" << std::endl;
	}

	if(path_.is_available())
	{
		//// Positioning --------------------
		const sf::Vector2f actual_position = getPosition();
		const sf::Vector2f direction = Normalized(destination_ - actual_position);
		sf::Vector2f new_position = sf::Vector2f(0, 0);

		if (Magnitude(destination_ - actual_position) < 16.0f) {
			new_position = destination_;
			destination_ = path_.GetNextStep();
		}else
		{
			new_position = actual_position + sf::Vector2f(direction.x * delta_time * linear_speed_, direction.y * delta_time * linear_speed_);
		}
		setPosition(new_position);
		sprite_.setPosition(getPosition());
		frame_.setPosition(getPosition());
	}
}

sf::Vector2f Walker::GetLastDestination() const
{
	return destination_;
}
