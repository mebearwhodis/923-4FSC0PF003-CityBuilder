#include "gameplay/view.h"

View::View(const sf::Vector2f& centre, const sf::Vector2f& size)
    : view_(centre, size) {}

void View::HandleInput(sf::RenderWindow& window)
{
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

    // Calculate where the view would move to
    sf::Vector2f proposed_center = view_.getCenter() + movement;
    const float half_width = view_.getSize().x / 2.0f;
    const float half_height = view_.getSize().y / 2.0f;

    // Ensure proposedCenter stays within bounds
    if (proposed_center.x - half_width < bounds_.left) {
        proposed_center.x = bounds_.left + half_width;
    }
    if (proposed_center.y - half_height < bounds_.top) {
        proposed_center.y = bounds_.top + half_height;
    }
    if (proposed_center.x + half_width > bounds_.left + bounds_.width) {
        proposed_center.x = bounds_.left + bounds_.width - half_width;
    }
    if (proposed_center.y + half_height > bounds_.top + bounds_.height) {
        proposed_center.y = bounds_.top + bounds_.height - half_height;
    }

    // Apply the corrected movement to the view
    view_.setCenter(proposed_center);
}

void View::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
	    const float zoom_factor = 1.1f;
        if (event.mouseWheelScroll.delta > 0 && zoom_power() < 20) {
            view_.zoom(1.f / zoom_factor);
            set_zoom_power(zoom_power() + 1);
        }
        else if (event.mouseWheelScroll.delta < 0 && zoom_power() > 0) {
            view_.zoom(zoom_factor);
            set_zoom_power(zoom_power() - 1);
        }

	    const sf::Vector2f new_center = view_.getCenter();

        // Adjust view center to keep within bounds
        view_.setCenter(
            std::max(bounds_.left + view_.getSize().x / 2.f, std::min(new_center.x, bounds_.left + bounds_.width - view_.getSize().x / 2.f)),
            std::max(bounds_.top + view_.getSize().y / 2.f, std::min(new_center.y, bounds_.top + bounds_.height - view_.getSize().y / 2.f))
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
	    const sf::Vector2i current_mouse_position = sf::Mouse::getPosition(window);
	    const sf::Vector2f delta = window.mapPixelToCoords(last_mouse_position_) - window.mapPixelToCoords(current_mouse_position);
        view_.move(delta);
        last_mouse_position_ = current_mouse_position;

        // Block view from going outside the map
        CheckBounds();
    }
}

void View::ApplyView(sf::RenderWindow& window) const
{
    window.setView(view_);
}

void View::SetCenter(const sf::Vector2f& center)
{
    view_.setCenter(center);
}

void View::SetBounds(const sf::FloatRect& bounds)
{
    bounds_ = bounds;
}

void View::CheckBounds()
{
	const sf::Vector2f center = view_.getCenter();
	const sf::Vector2f half_size = view_.getSize() / 2.0f;

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