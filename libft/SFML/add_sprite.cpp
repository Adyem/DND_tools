#include "SFML.hpp"
#include <SFML/Graphics.hpp>
#include <new>
#include <string>
#include <unordered_map>

sf::Texture* GraphicsData::loadTexture(const char* fileName)
{
	try
	{
    	std::string fname(fileName);
    	auto it = _textureCache.find(fname);
    	if (it != _textureCache.end())
        	return it->second.get();
    	sf::Texture* newTexture = new(std::nothrow) sf::Texture();
    	if (!newTexture || !newTexture->loadFromFile(fileName))
    	{
        	delete newTexture;
        	return nullptr;
   		}
   		ft_sharedptr<sf::Texture> texturePtr(newTexture);
    	if (texturePtr.getErrorCode())
    	{
    	    delete newTexture;
    	    return nullptr;
   		 }
    	_textureCache[fname] = texturePtr;
    	return newTexture;
	}
	catch(...)
	{
		return (nullptr);
	}
}

void GraphicsData::addSpriteHelper(sf::Texture* texture, const t_coordinate* position)
{
	try
	{
    	bool hasPosition = (position != nullptr);
    	t_coordinate sfCoord;
    	if (hasPosition)
    	    sfCoord = translateCoordinates(*position);
    	for (size_t i = 0; i < _object.size(); ++i)
    	{
    	    sf::Drawable* drawable = _object[i]->drawable.get();
    	    sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(drawable);
    	    if (sprite && sprite->getTexture() == texture)
    	    {
    	        if (hasPosition)
    	        {
    	            ft_sharedptr<t_object_coordinates> coords(new t_object_coordinates());
    	            if (coords.getErrorCode())
    	            {
    	                this->_error = 1;
    	                return;
    	            }
    	            coords->virtual_location = sfCoord;
    	            _object[i]->coordinates.push_back(coords);
    	            if (_object[i]->coordinates.getError())
    	            {
    	                this->_error = 1;
    	                return;
    	            }
    	        }
    	        return;
    	    }
    	}
    	sf::Sprite* newSprite = new sf::Sprite();
    	newSprite->setTexture(*texture);
    	if (hasPosition)
        	newSprite->setPosition(sfCoord.x, sfCoord.y);
    	ft_sharedptr<t_graphics_object> gfxObj(new t_graphics_object());
    	if (gfxObj.getErrorCode())
    	{
    	    this->_error = 1;
    	    return;
    	}
    	gfxObj->drawable = ft_sharedptr<sf::Drawable>(newSprite);
    	if (gfxObj->drawable.getErrorCode())
    	{
    	    this->_error = 1;
    	    return;
    	}
    	if (hasPosition)
    	{
    	    ft_sharedptr<t_object_coordinates> coords(new t_object_coordinates());
    	    if (coords.getErrorCode())
    	    {
    	        this->_error = 1;
    	        return;
    	    }
    	    coords->virtual_location = sfCoord;
    	    gfxObj->coordinates.push_back(coords);
    	    if (gfxObj->coordinates.getError())
        	{
        	    this->_error = 1;
        	    return;
        	}
    	}
	    _object.push_back(gfxObj);
	    if (_object.getError())
	        this->_error = 1;
	}
	catch(...)
	{
		this->_error = 1;
	}
	return ;
}

void GraphicsData::addSpriteFromFile(const char *fileName)
{
    sf::Texture* texture = loadTexture(fileName);
    if (!texture)
    {
        this->_error = 1;
        return;
    }
    addSpriteHelper(texture, nullptr);
}

void GraphicsData::addSpriteFromFile(const char *fileName, const t_coordinate &position)
{
    sf::Texture* texture = loadTexture(fileName);
    if (!texture)
    {
        this->_error = 1;
        return;
    }
    addSpriteHelper(texture, &position);
}

void GraphicsData::addSprite(const sf::Texture &texture, const t_coordinate &position)
{
    addSpriteHelper(const_cast<sf::Texture*>(&texture), &position);
}
