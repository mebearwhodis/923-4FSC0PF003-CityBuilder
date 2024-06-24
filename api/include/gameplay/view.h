#ifndef API_VIEW_H_
#define API_VIEW_H_

#include <SFML/Graphics.hpp>

class View {
public:
    void init(sf::Vector2f size, sf::Vector2f center);
    void handleInput();
    sf::View getView();

private:
    sf::View view_;
};

#endif // API_VIEW_H_
