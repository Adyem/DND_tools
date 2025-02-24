#ifndef SFML_HPP
#define SFML_HPP

#include <SFML/Graphics.hpp>
#include "../Template/shared_ptr.hpp"
#include "../Template/vector.hpp"
#include "../Template/map.hpp"
#include "../CPP_class/string.hpp"
#include <unordered_map>

#ifndef DEBUG
 #define DEBUG 0
#endif

typedef struct s_coordinate
{
    float x = 0;
    float y = 0;
} t_coordinate;

typedef struct s_object_coordinates
{
    t_coordinate virtual_location;
    t_coordinate virtual_movement;
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

        void addSpriteFromFile(const char *fileName);
        void addSpriteFromFile(const char *fileName, const t_coordinate &position);
        void addSprite(const sf::Texture &texture, const t_coordinate &position);

		ft_sharedptr<t_graphics_object> createButton(const ft_string &label,
				const t_coordinate &virtualPos, const t_coordinate &virtualSize,
				const sf::Font &font, sf::Color buttonColor = sf::Color::White,
				sf::Color textColor = sf::Color::Black, const sf::Texture *spriteTexture = nullptr);

        sf::RenderWindow *_window;
        ft_vector<ft_sharedptr<t_graphics_object>> _object;
        int _error;

    private:
        t_coordinate _window_size;
        ft_map<ft_string, ft_sharedptr<sf::Texture>> _textureCache;

        t_coordinate translateCoordinates(const t_coordinate& customCoord) const;

        sf::Texture* loadTexture(const char* fileName);
        void addSpriteHelper(sf::Texture* texture, const t_coordinate* position);
};

#endif
