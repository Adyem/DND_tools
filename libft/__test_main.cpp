#include <SFML/Graphics.hpp>
#include <iostream>
#include "SFML/SFML.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    // Create a GraphicsData object with a window of 800x600 pixels and a title.
    GraphicsData graphics(800, 600, "Example Window");

    // Load a font (make sure "arial.ttf" is in your project folder)
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: Could not load font 'arial.ttf'" << std::endl;
        return -1;
    }

    // Define virtual positions and sizes for two buttons
    t_coordinate button1Pos{100.f, 100.f};
    t_coordinate button1Size{200.f, 50.f};

    t_coordinate button2Pos{100.f, 200.f};
    t_coordinate button2Size{200.f, 50.f};

    // Create buttons using the GraphicsData method. Note: spriteTexture is left as nullptr.
    auto button1 = graphics.createButton("Button 1", button1Pos, button1Size, font);
    auto button2 = graphics.createButton("Button 2", button2Pos, button2Size, font);

    // Add the buttons to the list of drawable objects.
    graphics._object.push_back(button1);
    graphics._object.push_back(button2);

    // Main loop: process events and draw the buttons.
    while (graphics._window->isOpen())
    {
        sf::Event event;
        while (graphics._window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                graphics._window->close();
        }

        graphics._window->clear(sf::Color::Black);

        // Draw each graphics object (assuming each object's 'drawable' member is correctly set).
        for (auto& obj : graphics._object)
        {
            graphics._window->draw(*(obj->drawable));
        }

        graphics._window->display();
    }

    return 0;
}
