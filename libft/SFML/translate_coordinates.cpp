#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML.hpp"

t_coordinate GraphicsData::translateCoordinates(const t_coordinate& customCoord) const
{
    t_coordinate screenCoord;
    screenCoord.x = (customCoord.x / 1000.0f) * _window_size.x;
    screenCoord.y = (customCoord.y / 1000.0f) * _window_size.y;
    return (screenCoord);
}
