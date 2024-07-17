#ifndef API_UI_TEXTBOX_H_
#define API_UI_TEXTBOX_H_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "graphics/resource_manager.h"

class TextBox : public sf::Drawable, public sf::Transformable
{
	private:
	sf::Text text_;
	sf::Font font_;
	bool is_visible_ = true;
	bool can_be_hidden_;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	TextBox(sf::Vector2f positionRelativeToView, std::string text, int size, sf::Color color, bool visible);
	TextBox() = default;

	bool is_visible() const { return is_visible_; }
	void toggle_visible() { is_visible_ = !is_visible_; }
	bool can_be_hidden() const { return can_be_hidden_; }
	void update_textbox(sf::Color colour, std::string text);
};
#endif // API_UI_TEXTBOX_H_
