#ifndef API_UI_UI_BUTTON_H_
#define API_UI_UI_BUTTON_H_

#include <functional>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>

#include "graphics/resource_manager.h"

class UiButton : public sf::Drawable, public sf::Transformable
{
private:
	sf::Font font_;
	sf::Texture texture_up_;
	sf::Texture texture_down_;
	sf::Sprite sprite_;
	sf::Text text_;
	bool is_visible_ = true;
	bool is_pressed_ = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	UiButton(sf::Vector2f position_relative_to_view, UiTexture up_texture_name, bool visible);

	std::function<void()> callback_;

	bool ContainsMouse(const sf::Event::MouseButtonEvent& event) const;
	void HandleEvent(const sf::Event& event);
	void ToggleVisible() { is_visible_ = !is_visible_; }

	bool is_pressed() const { return is_pressed_; }
	bool is_visible() const { return is_visible_; }
};

#endif  // API_UI_UI_BUTTON_H_