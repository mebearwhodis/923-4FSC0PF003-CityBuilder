#ifndef API_UI_UIBUTTON_H_
#define API_UI_UIBUTTON_H_

#include <functional>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>


class UiButton : public sf::Drawable, public sf::Transformable
{
private:
	sf::RectangleShape background_;
	sf::Sprite sprite_;
	sf::Texture textureBG_;
	sf::Text text_;


	sf::Color normalColor_;
	sf::Color pressedColor_;

	sf::Vector2f normalSize_;
	sf::Vector2f pressedSize_;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	UiButton(sf::Vector2f position, sf::Vector2f size, sf::Color base_color, const std::string& text, const sf::Font& font);
	void HandleEvent(const sf::Event& event);

	//Callback pour avoir une fonction spécifique au bouton
	//void(*callback_)();
	std::function<void()> callback_;
};

#endif  // API_UI_UIBUTTON_H_