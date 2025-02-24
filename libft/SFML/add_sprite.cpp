#include "SFML.hpp"
#include "../CPP_class/string.hpp"
#include <SFML/Graphics.hpp>
#include <new>
#include <string>
#include <unordered_map>

sf::Texture* GraphicsData::loadTexture(const char* fileName)
{
    ft_string fname(fileName);
    auto it = _textureCache.find(fname);
    if (it != _textureCache.end())
        return (it->second.get());
    sf::Texture* newTexture = new(std::nothrow) sf::Texture();
    if (!newTexture)
    {
        this->_error = 1;
        sf::err() << "Memory allocation for sf::Texture failed: " << fileName << std::endl;
        return (ft_nullptr);
    }
    if (!newTexture->loadFromFile(fileName))
    {
        this->_error = 1;
        sf::err() << "Failed to load texture from file: " << fileName << std::endl;
        delete newTexture;
        return (ft_nullptr);
    }
    ft_sharedptr<sf::Texture> texturePtr(newTexture);
    if (texturePtr.getErrorCode())
    {
        this->_error = 1;
        sf::err() << "ft_sharedptr error for texture: " << fileName << std::endl;
        delete newTexture;
        return (ft_nullptr);
    }
    _textureCache[fname] = texturePtr;
    return (newTexture);
}

void GraphicsData::addSpriteHelper(sf::Texture* texture, const t_coordinate* position)
{
    bool hasPosition = (position != nullptr);
    t_coordinate sfCoord;
    if (hasPosition)
        sfCoord = translateCoordinates(*position);

    sf::Sprite* newSprite = new(std::nothrow) sf::Sprite();
    if (!newSprite)
    {
        this->_error = 1;
        sf::err() << "Memory allocation for sf::Sprite failed." << std::endl;
        return ;
    }
    newSprite->setTexture(*texture);
    if (hasPosition)
        newSprite->setPosition(sfCoord.x, sfCoord.y);

    ft_sharedptr<t_graphics_object> gfxObj(new t_graphics_object());
    if (gfxObj.getErrorCode())
    {
        this->_error = 1;
        sf::err() << "ft_sharedptr error for t_graphics_object." << std::endl;
        return ;
    }
    gfxObj->drawable = ft_sharedptr<sf::Drawable>(newSprite);
    if (gfxObj->drawable.getErrorCode())
    {
        this->_error = 1;
        sf::err() << "ft_sharedptr error for sf::Drawable." << std::endl;
        return ;
    }
    if (hasPosition)
    {
        ft_sharedptr<t_object_coordinates> coords(new t_object_coordinates());
        if (coords.getErrorCode())
        {
            this->_error = 1;
            sf::err() << "ft_sharedptr error for t_object_coordinates." << std::endl;
            return ;
        }
        coords->virtual_location = sfCoord;
        gfxObj->coordinates.push_back(coords);
        if (gfxObj->coordinates.getError())
        {
            this->_error = 1;
            sf::err() << "Error adding coordinates to graphics object." << std::endl;
            return ;
        }
    }
    _object.push_back(gfxObj);
    if (_object.getError())
    {
        this->_error = 1;
        sf::err() << "Error pushing graphics object to container." << std::endl;
    }
	return ;
}

void GraphicsData::addSpriteFromFile(const char *fileName)
{
    sf::Texture* texture = loadTexture(fileName);
    if (!texture)
    {
        this->_error = 1;
        return ;
    }
    addSpriteHelper(texture, ft_nullptr);
	return ;
}

void GraphicsData::addSpriteFromFile(const char *fileName, const t_coordinate &position)
{
    sf::Texture* texture = loadTexture(fileName);
    if (!texture)
    {
        this->_error = 1;
        return ;
    }
    addSpriteHelper(texture, &position);
	return ;
}

void GraphicsData::addSprite(const sf::Texture &texture, const t_coordinate &position)
{
    addSpriteHelper(const_cast<sf::Texture*>(&texture), &position);
	return ;
}

