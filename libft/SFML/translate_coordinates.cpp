#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML.hpp"

t_coordinate GraphicsData::translateCoordinates(const t_coordinate& customCoord) const
{
    t_coordinate screenCoord;
    screenCoord.width = (customCoord.width / 1000.0f) * _window_size.width;
    screenCoord.height = (customCoord.height / 1000.0f) * _window_size.height;
    return screenCoord;
}
