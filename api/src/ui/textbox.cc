#include "ui/textbox.h"

TextBox::TextBox(const sf::Vector2f position_relative_to_view, const std::string& text, const int size, const sf::Color color, const bool visible)
{
	text_ = sf::Text(text, ResourceManager::Get().font());
	text_.setCharacterSize(size);
	text_.setFillColor(color);
	// Set origin to the bottom-right corner of the text bounds
	const sf::FloatRect text_bounds = text_.getLocalBounds();
	text_.setOrigin(text_bounds.left + text_bounds.width, text_bounds.top + text_bounds.height);
	text_.setPosition(position_relative_to_view);
	is_visible_ = visible;
	can_be_hidden_ = !visible;
}

void TextBox::UpdateTextbox(const sf::Color colour, const std::string& text)
{
	text_.setFillColor(colour);
	text_.setString(text);
	const sf::FloatRect text_bounds = text_.getLocalBounds();
	text_.setOrigin(text_bounds.left + text_bounds.width, text_bounds.top + text_bounds.height);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if(is_visible_)
	{
		target.draw(text_, states);
	}
}