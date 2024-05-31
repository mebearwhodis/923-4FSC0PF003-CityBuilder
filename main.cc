#include <iostream>
#include <SFML/Graphics.hpp>
#include "api/include/ui/UIButton.h"

void mainCallback()
{
    std::cout << "callback uwu" << std::endl;
}

int main()
{
    sf::Font font;
    if (!font.loadFromFile("../resources/fonts/arial.ttf"))
    {
        std::cout << "Font missing." << std::endl;
    }
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    UiButton secondButton(sf::Vector2f(400, 300), sf::Vector2f(100, 100), sf::Color::Cyan, "Bouton", font);

    secondButton.callback_ = mainCallback;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle UI Events
            secondButton.HandleEvent(event);

        }

        // clear the window with black color
        window.clear(sf::Color::Magenta);

        // draw everything here...
        // window.draw(...);
        window.draw(secondButton);

        // end the current frame
        window.display();
    }

    return 0;
}
