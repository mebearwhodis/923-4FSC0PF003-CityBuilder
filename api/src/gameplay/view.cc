#include "gameplay/view.h"

#include <iostream>

View::View(const sf::Vector2f& center, const sf::Vector2f& size)
    : view_(center, size) {}

void View::handleInput(sf::RenderWindow& window) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= 64.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += 64.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= 64.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += 64.f;
    }


    //TODO do same for mousewheel drag
    // Calculate where the view would move to
    sf::Vector2f proposedCenter = view_.getCenter() + movement;
    float halfWidth = view_.getSize().x / 2.0f;
    float halfHeight = view_.getSize().y / 2.0f;

    // Ensure proposedCenter stays within bounds
    if (proposedCenter.x - halfWidth < bounds_.left) {
        proposedCenter.x = bounds_.left + halfWidth;
    }
    if (proposedCenter.y - halfHeight < bounds_.top) {
        proposedCenter.y = bounds_.top + halfHeight;
    }
    if (proposedCenter.x + halfWidth > bounds_.left + bounds_.width) {
        proposedCenter.x = bounds_.left + bounds_.width - halfWidth;
    }
    if (proposedCenter.y + halfHeight > bounds_.top + bounds_.height) {
        proposedCenter.y = bounds_.top + bounds_.height - halfHeight;
    }

    // Apply the corrected movement to the view
    view_.setCenter(proposedCenter);
}




void View::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        float zoomFactor = 1.1f;
        if (event.mouseWheelScroll.delta > 0 && zoom_power() < 20) {
            view_.zoom(1.f / zoomFactor);
            set_zoom_power(zoom_power() + 1);
            std::cout << zoom_power() << std::endl;
        }
        else if (event.mouseWheelScroll.delta < 0 && zoom_power() > 0) {
            view_.zoom(zoomFactor);
            set_zoom_power(zoom_power() - 1);
            std::cout << zoom_power() << std::endl;
        }

        sf::Vector2f newCenter = view_.getCenter();

        // Adjust view center to keep within bounds
        view_.setCenter(
            std::max(bounds_.left + view_.getSize().x / 2.f, std::min(newCenter.x, bounds_.left + bounds_.width - view_.getSize().x / 2.f)),
            std::max(bounds_.top + view_.getSize().y / 2.f, std::min(newCenter.y, bounds_.top + bounds_.height - view_.getSize().y / 2.f))
        );
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Middle) {
            mouse_dragging_ = true;
            last_mouse_position_ = sf::Mouse::getPosition(window);
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Middle) {
            mouse_dragging_ = false;
        }
    }
    else if (event.type == sf::Event::MouseMoved && mouse_dragging_) {
        sf::Vector2i current_mouse_position = sf::Mouse::getPosition(window);
        sf::Vector2f delta = window.mapPixelToCoords(last_mouse_position_) - window.mapPixelToCoords(current_mouse_position);
        view_.move(delta);
        last_mouse_position_ = current_mouse_position;

        // Block view from going outside the map
        checkBounds();
    }
}

void View::apply(sf::RenderWindow& window) {
    window.setView(view_);
}

void View::setCenter(const sf::Vector2f& center)
{
    view_.setCenter(center);
}

void View::setBounds(const sf::FloatRect& bounds) {
    bounds_ = bounds;
}

void View::checkBounds() {
    sf::Vector2f center = view_.getCenter();
    sf::Vector2f half_size = view_.getSize() / 2.0f;

    if (center.x - half_size.x < bounds_.left) {
        view_.setCenter(bounds_.left + half_size.x, center.y);
    }
    if (center.y - half_size.y < bounds_.top) {
        view_.setCenter(center.x, bounds_.top + half_size.y);
    }
    if (center.x + half_size.x > bounds_.left + bounds_.width) {
        view_.setCenter(bounds_.left + bounds_.width - half_size.x, center.y);
    }
    if (center.y + half_size.y > bounds_.top + bounds_.height) {
        view_.setCenter(center.x, bounds_.top + bounds_.height - half_size.y);
    }
}