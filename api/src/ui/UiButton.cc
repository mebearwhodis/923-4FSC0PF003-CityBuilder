#include <ui/UiButton.h>

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>


UiButton::UiButton(const sf::Vector2f position, const sf::Vector2f size, const sf::Color base_color, const std::string& text, const sf::Font& font)
{
	setPosition(position.x - size.x / 2, position.y - size.y / 2); //Button inherits from Transformable, so it has its own position
	background_.setPosition(getPosition());
	//background_.setPosition(position);
	background_.setSize(size);
	background_.setFillColor(base_color);

	textureBG_.loadFromFile("../resources/sprites/ui/red_button10.png");

	sprite_.setColor(sf::Color::White);
	sprite_.setTexture(textureBG_);
	sprite_.setOrigin(size.x / 2, size.y / 2);


	normalColor_ = base_color;
	pressedColor_ = sf::Color(
		base_color.r * 0.75,
		base_color.g * 0.75,
		base_color.b * 0.75,
		base_color.a);
	normalSize_ = size;
	pressedSize_ = sf::Vector2f(size.x * 0.75, size.y * 0.75);
	text_.setFont(font);
	text_.setString(text);
	text_.setCharacterSize(50);
	text_.setPosition(getPosition());
	if (base_color == sf::Color::Black)
	{
		text_.setFillColor(sf::Color::White);
	}
	else
	{
		text_.setFillColor(sf::Color::Black);
	}

	//sf::FloatRect textBounds = text_.getLocalBounds();
	//text_.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	//text_.setPosition(position + size / 2.0f);
}

void UiButton::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	//states.transform *= getTransform();
	target.draw(background_, states);
	target.draw(sprite_, states);
	target.draw(text_, states);
}

void UiButton::HandleEvent(const sf::Event& event)
{

	//Check for mouse button pressed event
	if (event.type == sf::Event::MouseButtonPressed)
	{
		//Check if the left mouse button is pressed
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			float mouseX = static_cast<float>(event.mouseButton.x);
			float mouseY = static_cast<float>(event.mouseButton.y);

			//Check if the mouseclick is inside the drawable shape
			if (background_.getGlobalBounds().contains(mouseX, mouseY))
			{
				std::cout << "Mouse clicked inside the shape." << std::endl;
				background_.setFillColor(pressedColor_);
				background_.setScale(0.5f, 0.5f);
			}
		}
	}

	//Check for mouse button released event
	if (event.type == sf::Event::MouseButtonReleased)
	{
		//Check if the left mouse button is pressed
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			float mouseX = static_cast<float>(event.mouseButton.x);
			float mouseY = static_cast<float>(event.mouseButton.y);

			//Check if the mouseclick is inside the drawable shape
			if (background_.getGlobalBounds().contains(mouseX, mouseY))
			{
				std::cout << "Mouse released inside the shape." << std::endl;
				background_.setFillColor(normalColor_);
				background_.setSize(normalSize_);
			}
		}
	}
}
