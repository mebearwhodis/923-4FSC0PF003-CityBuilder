#ifndef API_GAMEPLAY_VIEW_H_
#define API_GAMEPLAY_VIEW_H_

#include <SFML/Graphics.hpp>

class View {
private:
    bool mouse_dragging_ = false;
    int zoom_power_ = 10;
    sf::View view_;
    sf::Vector2i last_mouse_position_;
    sf::FloatRect bounds_; // Bounds of the map

    void CheckBounds();

public:
    View(const sf::Vector2f& centre, const sf::Vector2f& size);

    void ApplyView(sf::RenderWindow& window) const;
    void HandleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void HandleInput(sf::RenderWindow& window);
    void SetCenter(const sf::Vector2f& center);
    void SetBounds(const sf::FloatRect& bounds);

    int zoom_power() const { return zoom_power_; }
    sf::View view() const { return view_; }
    void set_zoom_power(const int value) { zoom_power_ = value; }
};

#endif // API_GAMEPLAY_VIEW_H_
