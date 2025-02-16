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
    float x = 0;
    float y = 0;
} t_coordinate;

typedef struct s_object_coordinates
{
	t_coordinate virtual_location;
	t_coordinate actual_location;
	t_coordinate virtual_movement;
	t_coordinate actual_movement;
} t_object_coordinates;

typedef struct s_graphics_object
{
	ft_vector<ft_sharedptr<t_object_coordinates>> coordinates;
	ft_sharedptr<sf::Drawable> drawable;
} t_graphics_object;

class GraphicsData
{
	public:
    	GraphicsData() = delete;

    	GraphicsData(unsigned int width, unsigned int height, const char* title);
    	~GraphicsData();

		void addSprite(const sf::Texture &texture, const t_coordinate &position);
		void addSpriteFromFile(const char *fileName);
		void addSpriteFromFile(const char *fileName, const t_coordinate &position);

    	sf::RenderWindow *_window;
		ft_vector<ft_sharedptr<t_graphics_object>> _object;
		int _error;

	private:
		t_coordinate _window_size;

		t_coordinate translateCoordinates(const t_coordinate& customCoord) const;
};

#endif
