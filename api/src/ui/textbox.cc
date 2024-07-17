#include "ui/textbox.h"

#include "gameplay/economy_manager.h"


TextBox::TextBox(sf::Vector2f positionRelativeToView, std::string text, int size, sf::Color color, bool visible)
{

	text_ = sf::Text(text, ResourceManager::Get().GetFont());
	text_.setCharacterSize(size);
	text_.setFillColor(color);
	// Set origin to the bottom-right corner of the text bounds
	const sf::FloatRect text_bounds = text_.getLocalBounds();
	text_.setOrigin(text_bounds.left + text_bounds.width, text_bounds.top + text_bounds.height);
	text_.setPosition(positionRelativeToView);
	is_visible_ = visible;
	can_be_hidden_ = !visible;
}

void TextBox::update_textbox(sf::Color colour, std::string text)
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