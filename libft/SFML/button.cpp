#include "../Template/shared_ptr.hpp"
#include "button.hpp"
#include "SFML.hpp"

ft_sharedptr<t_graphics_object> GraphicsData::createButton(const std::string &label,
		const t_coordinate &virtualPos, const t_coordinate &virtualSize,
		const sf::Font &font, sf::Color buttonColor,
		sf::Color textColor, const sf::Texture *spriteTexture)
{
	try
	{
    	t_coordinate pos = translateCoordinates(virtualPos);
    	t_coordinate size;
    	size.x = (virtualSize.x / 1000.0f) * _window_size.x;
    	size.y = (virtualSize.y / 1000.0f) * _window_size.y;
    	ft_sharedptr<sf::RectangleShape> buttonShape
			(new sf::RectangleShape(sf::Vector2f(size.x, size.y)));
    	buttonShape->setPosition(sf::Vector2f(pos.x, pos.y));
    	buttonShape->setFillColor(buttonColor);
    	ft_sharedptr<sf::Sprite> buttonSprite = nullptr;
    	if (spriteTexture)
		{
    	    buttonSprite = ft_sharedptr<sf::Sprite>(new sf::Sprite(*spriteTexture));
    	    sf::Vector2u texSize = spriteTexture->getSize();
    	    buttonSprite->setScale(size.x / texSize.x, size.y / texSize.y);
    	    buttonSprite->setPosition(sf::Vector2f(pos.x, pos.y));
    	}
    	ft_sharedptr<sf::Text> buttonText(new sf::Text());
    	buttonText->setFont(font);
    	buttonText->setString(label);
    	buttonText->setFillColor(textColor);
    	unsigned int charSize = static_cast<unsigned int>(size.y * 0.6f);
    	buttonText->setCharacterSize(charSize);
    	sf::FloatRect textRect = buttonText->getLocalBounds();
    	buttonText->setOrigin(textRect.left + textRect.width / 2.0f,
    	                      textRect.top + textRect.height / 2.0f);
    	buttonText->setPosition(sf::Vector2f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f));
    	ft_sharedptr<t_graphics_object> buttonObject(new t_graphics_object());
    	ft_sharedptr<sf::Drawable> compositeButton
			(new Button(buttonShape, buttonText, buttonSprite));
    	buttonObject->drawable = compositeButton;
    	ft_sharedptr<t_object_coordinates> coords(new t_object_coordinates());
    	coords->virtual_location = virtualPos;
    	buttonObject->coordinates.push_back(coords);
    	return buttonObject;
	}
	catch (...)
	{
		return (nullptr);
	}
}

Button::Button(ft_sharedptr<sf::RectangleShape> shape, ft_sharedptr<sf::Text> text,
		ft_sharedptr<sf::Sprite> sprite)
    : buttonShape(shape), buttonText(text), buttonSprite(sprite)
{
    return ;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	try
	{
		if (buttonSprite)
			target.draw(*buttonSprite, states);
		target.draw(*buttonShape, states);
		target.draw(*buttonText, states);
		return ;
	}
	catch (...)
	{
		return ;
	}
}
