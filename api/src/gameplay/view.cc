
#include "gameplay/view.h"

void View::init(sf::Vector2f size, sf::Vector2f center) {
    view_.setSize(size);
    view_.setCenter(center);
}

void View::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        view_.move(-50.f, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        view_.move(50.f, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        view_.move(0.f, -50.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        view_.move(0.f, 50.f);
    }
}

sf::View View::getView() {
    return view_;
}
