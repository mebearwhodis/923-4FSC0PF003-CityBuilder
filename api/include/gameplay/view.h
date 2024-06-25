#ifndef API_VIEW_H_
#define API_VIEW_H_

#include <SFML/Graphics.hpp>

class View {
public:
    View(const sf::Vector2f& center, const sf::Vector2f& size);

    void handleInput(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void apply(sf::RenderWindow& window);
    sf::View view() const { return view_; }
    void setCenter(const sf::Vector2f& center);
    void setBounds(const sf::FloatRect& bounds);
    int zoom_power() { return zoom_power_; }
    void set_zoom_power(int value) { zoom_power_ = value; }

private:
    sf::View view_;
    bool mouse_dragging_ = false;
    sf::Vector2i last_mouse_position_;
    sf::FloatRect bounds_; // Bounds of the map
    float min_zoom_ = 1.0f; // Minimum zoom level
    float max_zoom_ = 2.0f; // Maximum zoom level
    int zoom_power_ = 10;


    void checkBounds();
};

#endif // VIEW_H
