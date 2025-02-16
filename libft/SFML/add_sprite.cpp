#include "SFML.hpp"
#include <SFML/Graphics.hpp>
#include <new>
#include <string>

void GraphicsData::addSpriteFromFile(const char *fileName)
{
    try
    {
        sf::Texture* texture = new(std::nothrow) sf::Texture();
        if (!texture->loadFromFile(fileName))
        {
            delete texture;
            this->_error = 1;
            return;
        }
        for (size_t i = 0; i < _object.size(); ++i)
        {
            sf::Drawable* drawable = _object[i]->drawable.get();
            sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(drawable);
            if (sprite)
                if (sprite->getTexture() == texture)
                    return;
        }
        sf::Sprite* newSprite = new sf::Sprite();
        newSprite->setTexture(*texture);

        ft_sharedptr<t_graphics_object> gfxObj(new t_graphics_object());
        if (gfxObj.getErrorCode())
        {
            this->_error = 1;
            return;
        }
        gfxObj->drawable = ft_sharedptr<sf::Drawable>(newSprite);
        this->_object.push_back(gfxObj);
        if (this->_object.getError())
            this->_error = 1;
    }
    catch (...)
    {
        this->_error = 1;
    }
    return;
}

void GraphicsData::addSpriteFromFile(const char *fileName, const t_coordinate &position)
{
    try
    {
        sf::Texture* texture = new(std::nothrow) sf::Texture();
        if (!texture->loadFromFile(fileName))
        {
            delete texture;
            this->_error = 1;
            return ;
        }
        t_coordinate sfCoord = translateCoordinates(position);
        for (size_t i = 0; i < _object.size(); ++i)
        {
            sf::Drawable* drawable = _object[i]->drawable.get();
            sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(drawable);
            if (sprite)
            {
                if (sprite->getTexture() == texture)
                {
                    ft_sharedptr<t_object_coordinates> coords(new t_object_coordinates());
                    if (coords.getErrorCode())
                    {
                        this->_error = 1;
                        return ;
                    }
                    coords->virtual_location = sfCoord;
                    coords->actual_location  = sfCoord;
                    _object[i]->coordinates.push_back(coords);
                    if (_object[i]->coordinates.getError())
                    {
                        this->_error = 1;
                        return ;
                    }
                    return ;
                }
            }
        }
        sf::Sprite* newSprite = new sf::Sprite();
        newSprite->setTexture(*texture);
        newSprite->setPosition(sfCoord.x, sfCoord.y);
        ft_sharedptr<t_graphics_object> gfxObj(new t_graphics_object());
        if (gfxObj.getErrorCode())
        {
            this->_error = 1;
            return ;
        }
        gfxObj->drawable = ft_sharedptr<sf::Drawable>(newSprite);
        if (gfxObj->drawable.getErrorCode())
        {
            this->_error = 1;
            return ;
        }
        ft_sharedptr<t_object_coordinates> coords(new t_object_coordinates());
        if (coords.getErrorCode())
        {
            this->_error = 1;
            return ;
        }
        coords->virtual_location = sfCoord;
        coords->actual_location  = sfCoord;
        gfxObj->coordinates.push_back(coords);
        if (gfxObj.getErrorCode())
        {
            this->_error = 1;
            return ;
        }
        this->_object.push_back(gfxObj);
        if (this->_object.getError())
            this->_error = 1;
    }
    catch (...)
    {
        this->_error = 1;
    }
    return ;
}


void GraphicsData::addSprite(const sf::Texture &texture, const t_coordinate &position)
{
    try
    {
        for (size_t i = 0; i < _object.size(); ++i)
        {
            sf::Drawable* drawable = _object[i]->drawable.get();
            sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(drawable);
            if (sprite && sprite->getTexture() == &texture)
            {
                ft_sharedptr<t_object_coordinates> coords(new t_object_coordinates());
                if (coords.getErrorCode())
                {
                    this->_error = 1;
                    return ;
                }
                _object[i]->coordinates.push_back(coords);
                if (_object[i]->coordinates.getError())
                {
                    this->_error = 1;
                    return ;
                }
                return ;
            }
        }
        sf::Sprite* newSprite = new sf::Sprite();
        newSprite->setTexture(texture);
        t_coordinate sfCoord = translateCoordinates(position);
        newSprite->setPosition(sfCoord.x, sfCoord.y);
        ft_sharedptr<t_graphics_object> gfxObj(new t_graphics_object());
        gfxObj->drawable = ft_sharedptr<sf::Drawable>(newSprite);
        if (gfxObj->drawable.getErrorCode())
        {
            this->_error = 1;
            return ;
        }
        ft_sharedptr<t_object_coordinates> coords(new t_object_coordinates());
        if (coords.getErrorCode())
        {
            this->_error = 1;
            return ;
        }
        gfxObj->coordinates.push_back(coords);
        if (gfxObj.getErrorCode())
        {
            this->_error = 1;
            return ;
        }
        this->_object.push_back(gfxObj);
        if (this->_object.getError())
            this->_error = 1;
    }
    catch (...)
    {
        this->_error = 1;
    }
    return ;
}
