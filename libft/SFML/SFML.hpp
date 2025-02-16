#ifndef SFML_HPP
#define SFML_HPP

#include <SFML/Graphics.hpp>
#include "../Template/shared_ptr.hpp"
#include "../Template/vector.hpp"

#ifndef DEBUG
# define DEBUG 0
#endif

typedef struct s_coordinate
{
    float width;
    float height;
} t_coordinate;

typedef struct s_object_coordinates
{
	float	location_x;
	float	location_y;
	float	movement_x;
	float	movement_y;
} t_object_coordinates;

typedef struct s_graphics_object
{
	ft_vector<ft_sharedptr<t_object_coordinates>> object;
} t_graphics_object;

class GraphicsData
{
	public:
    	GraphicsData() = delete;

    	GraphicsData(unsigned int width, unsigned int height, const char* title);
    	~GraphicsData();

    	sf::RenderWindow *_window;
		ft_vector<ft_sharedptr<t_graphics_object>> _object;
		int _error;

	private:
		t_coordinate _window_size;

		t_coordinate translateCoordinates(const t_coordinate& customCoord) const;
};

#endif
