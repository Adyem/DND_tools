#include <SFML/Graphics.hpp>
#include "../CPP_class/nullptr.hpp"
#include <exception>

sf::RenderWindow* createWindow(unsigned int width, unsigned int height, const std::string& title)
{
    try
	{
        sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        return window;
    }
	catch (const std::exception& ex)
	{
        return (ft_nullptr);
    }
	catch (...)
	{
        return (ft_nullptr);
    }
}
