#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "../Template/shared_ptr.hpp"

class Button : public sf::Drawable {
	public:
		Button(ft_sharedptr<sf::RectangleShape> shape,
			   ft_sharedptr<sf::Text> text,
			   ft_sharedptr<sf::Sprite> sprite = nullptr);

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		ft_sharedptr<sf::RectangleShape> buttonShape;
		ft_sharedptr<sf::Text> buttonText;
		ft_sharedptr<sf::Drawable> buttonSprite;

		void	set_error(int error) const;
		int		get_error(void) const;

	private:
		mutable int	_error;
};

#endif
