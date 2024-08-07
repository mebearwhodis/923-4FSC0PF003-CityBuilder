#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif

#include <SFML/Graphics/RenderTarget.hpp>

#include "ui/ui_button.h"

UiButton::UiButton(const sf::Vector2f position_relative_to_view, UiTexture up_texture_name, const bool visible)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	setPosition(position_relative_to_view);

	texture_up_ = ResourceManager::Get().GetUiTexture(up_texture_name);
	texture_down_ = ResourceManager::Get().GetUiTexture(static_cast<UiTexture>(static_cast<int>(up_texture_name) +1));

	sprite_.setTexture(texture_up_);
	sprite_.setOrigin(sprite_.getTexture()->getSize().x / 2.0f, sprite_.getTexture()->getSize().y / 2.0f);
	sprite_.setColor(sf::Color::White);

	is_visible_ = visible;
}

void UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	states.transform *= getTransform();

	if(is_visible_)
	{
		target.draw(sprite_, states);
		target.draw(text_, states);
	}

}

bool UiButton::ContainsMouse(const sf::Event::MouseButtonEvent& event) const
{

#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	// Get the position of the mouse click
	const float mouse_x = static_cast<float>(event.x) - getPosition().x;
	const float mouse_y = static_cast<float>(event.y) - getPosition().y;

	// Check if the mouse click is inside the drawable shape
	if (sprite_.getGlobalBounds().contains(mouse_x, mouse_y)) {
		return true;
	}
	else
	{
		return false;
	}
}

void UiButton::HandleEvent(const sf::Event& event)
{

#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	//Check for mouse button pressed event
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (ContainsMouse(event.mouseButton))
		{
			//Check if the left mouse button is pressed
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				is_pressed_ = true;
				sprite_.setTexture(texture_down_);
			}
			return;
		}
	}


	//Check for mouse button released event
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (is_pressed_)
		{
			is_pressed_ = false;
			sprite_.setTexture(texture_up_);

			if (ContainsMouse(event.mouseButton))
			{

				//Check if the left mouse button is pressed
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (callback_) {
						callback_();
					}
					else
					{
						//std::cout << "No callback defined.";
					}
				}
			}
		}

	}
}