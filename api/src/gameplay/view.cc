#include "gameplay/view.h"

View::View(const sf::Vector2f& center, const sf::Vector2f& size)
    : view_(center, size) {}

//TODO move view with mouse movement if mousewheel is held down
//TODO Block view from going outside the map
void View::handleInput(sf::RenderWindow& window) {
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


//TODO Limit zoom
void View::handleEvent(sf::Event& event)
{
    // Handle zooming with mouse wheel scrolled event
    if (event.type == sf::Event::MouseWheelScrolled) {
        // Zoom factor and direction based on wheel movement
        float zoomFactor = 1.1f; // Adjust zoom factor as needed

        if (event.mouseWheelScroll.delta > 0) {
            view_.zoom(1.f / zoomFactor); // Zoom in
        }
        else if (event.mouseWheelScroll.delta < 0) {
            view_.zoom(zoomFactor); // Zoom out
        }
    }
}

void View::apply(sf::RenderWindow& window) {
    window.setView(view_);
}

