#ifndef API_UI_UIBUTTON_H_
#define API_UI_UIBUTTON_H_

#include <functional>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>
#include "../graphics/resource_manager.h"
#include "../gameplay/view.h"

class UiButton : public sf::Drawable, public sf::Transformable
{
private:
	sf::Font font_;
	sf::Sprite sprite_;

	sf::Text text_;



	bool button_pressed_ = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool ContainsMouse(const sf::Event::MouseButtonEvent& event) const;

public:
	UiButton(sf::Vector2f positionRelativeToView, sf::Color colorBase, std::string text, Resource textureName);
	void HandleEvent(const sf::Event& event);

	//Callback pour avoir une fonction spécifique au bouton
	std::function<void()> callback_;
};

#endif  // API_UI_UIBUTTON_H_