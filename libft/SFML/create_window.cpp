#include <SFML/Graphics.hpp>
#include "SFML.hpp"
#include "../CPP_class/nullptr.hpp"

GraphicsData::GraphicsData(unsigned int width, unsigned int height, const char* title)
    : _window(ft_nullptr),
      _error(0),
      _window_size{0.0f, 0.0f} 
{
    this->_window = new(std::nothrow) sf::RenderWindow(sf::VideoMode(width, height), title);
    if (!this->_window && !this->_window->isOpen())
    {
        this->_error = SFML_WINDOW_CREATE_FAIL;
		ft_errno = SFML_WINDOW_CREATE_FAIL;
    }
    else
    {
        this->_window_size.x = static_cast<float>(width);
        this->_window_size.y = static_cast<float>(height);
    }
	return ;
}

GraphicsData::~GraphicsData()
{
    delete this->_window;
	return ;
}
