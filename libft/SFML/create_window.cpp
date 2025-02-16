#include <SFML/Graphics.hpp>
#include "SFML.hpp"
#include "../CPP_class/nullptr.hpp"
#include <exception>

GraphicsData::GraphicsData(unsigned int width, unsigned int height, const char* title)
    : _window(ft_nullptr),
	_object(ft_nullptr),
	_error(0),
	_window_size{0.0f, 0.0f} 
{
    try
	{
        this->_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        this->_window_size.width = width;
        this->_window_size.height = height;
    }
    catch (const std::exception& ex)
	{
        this->_error = 1;
        this->_window = nullptr;
    }
    catch (...)
	{
        this->_error = 1;
        this->_window = nullptr;
    }
	return ;
}

GraphicsData::~GraphicsData()
{
    delete this->_window;
	return ;
}

