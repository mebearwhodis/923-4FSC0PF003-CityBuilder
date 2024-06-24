#ifndef API_VIEW_H_
#define API_VIEW_H_

#include <SFML/Graphics.hpp>

class View {
public:
    View(const sf::Vector2f& center, const sf::Vector2f& size);

    void handleInput(sf::RenderWindow& window);
    void handleEvent(sf::Event& event);
    void apply(sf::RenderWindow& window);
    sf::View view() const { return view_; }

private:
    sf::View view_;
};

#endif // VIEW_H
