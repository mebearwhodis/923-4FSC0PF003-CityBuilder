#include <ui/UiButton.h>

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>

#include "graphics/ResourceManager.h"


UiButton::UiButton(sf::Vector2f position, sf::Color colorBase, std::string text, ResourceManager::Resource textureName)
{
	setPosition(position); //Button inherits from Transformable, so it has its own position

	//Declare and load a font
	font_.loadFromFile("../resources/fonts/arial.ttf");

	//Create text
	text_ = sf::Text(text, font_);
	text_.setCharacterSize(42);
	text_.setFillColor(sf::Color::Black);
	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

	sprite_.setTexture(ResourceManager::Get().GetTexture(textureName));
	sprite_.setOrigin(sprite_.getTexture()->getSize().x /2.0f, sprite_.getTexture()->getSize().y / 2.0f);
	sprite_.setColor(sf::Color::White);

}

void UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(sprite_, states);
	target.draw(text_, states);

}

bool UiButton::ContainsMouse(const sf::Event& event)
{
	// Get the position of the mouse click
	float mouseX = static_cast<float>(event.mouseButton.x) - getPosition().x;
	float mouseY = static_cast<float>(event.mouseButton.y) - getPosition().y;

	// Check if the mouse click is inside the drawable shape
	if (sprite_.getGlobalBounds().contains(mouseX, mouseY)) {
		return true;
	}
	else
	{
		return false;
	}
}

void UiButton::HandleEvent(const sf::Event& event)
{

	//Check for mouse button pressed event
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if(ContainsMouse(event))
		{
			//Check if the left mouse button is pressed
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				buttonPressed_ = true;
				setScale(0.9f * getScale().x, 0.9f * getScale().y);
			}
		}
	}


	//Check for mouse button released event
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if(buttonPressed_)
		{
			setScale(getScale().x / 0.9f, getScale().y / 0.9f);
			buttonPressed_ = false;

			if (ContainsMouse(event))
			{

				//Check if the left mouse button is pressed
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (callback_) {
						callback_();
					}
					else
					{
						std::cout << "No callback defined.";
					}
				}
			}
		}

	}
}
