#include "SFML.hpp"

const sf::Sprite* getSprite(const ft_sharedptr<t_graphics_object>& obj)
{
    return (dynamic_cast<const sf::Sprite*>(obj->drawable.get()));
}

ft_vector<ft_sharedptr<t_graphics_object>> GraphicsData::getCollisionsForObject(
    const ft_sharedptr<t_graphics_object>& target) const
{
    ft_vector<ft_sharedptr<t_graphics_object>> collisions;
    const sf::Sprite* targetSprite = getSprite(target);
    if (!targetSprite)
    {
        this->_error = 1;
        return (collisions);
    }
    for (const auto& other : _object)
    {
        if (other.get() == target.get())
            continue ;
        const sf::Sprite* otherSprite = getSprite(other);
        if (!otherSprite)
            continue ;
        if (targetSprite->getGlobalBounds().intersects(otherSprite->getGlobalBounds()))
            collisions.push_back(other);
		if (collisions.getError())
		{
			this->_error = 1;
			return (collisions);
		}
    }
    return (collisions);
}
