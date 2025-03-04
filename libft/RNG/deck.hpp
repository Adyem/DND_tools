#ifndef DECK_HPP
#define DECK_HPP

#include "../Template/vector.hpp"
#include "../Template/swap.hpp"
#include "dice_roll.hpp"
#include <climits>

template<typename ElementType>
class deck : public ft_vector<ElementType*>
{
	public:
    	deck();
		~deck();
    
    	ElementType *getRandomElement();
    	ElementType *popRandomElement();
		void shuffle();
		ElementType *drawTopElement();
};

template<typename ElementType>
deck<ElementType>::deck() : ft_vector<ElementType*>()
{
	return ;
}

template<typename ElementType>
deck<ElementType>::~deck()
{
	return ;
}

template<typename ElementType>
ElementType *deck<ElementType>::getRandomElement()
{
    if (this->empty())
	{
		ft_errno = DECK_EMPTY;
        this->setError(DECK_EMPTY);
		return (ft_nullptr);
	}
    size_t index = static_cast<size_t>(ft_dice_roll(1, static_cast<int>(this->size())) - 1);
    return ((*this)[index]);
}

template<typename ElementType>
ElementType *deck<ElementType>::popRandomElement()
{
    if (this->empty())
	{
		ft_errno = DECK_EMPTY;
		this->setError(DECK_EMPTY);
		return (ft_nullptr);
	}
    size_t index = static_cast<size_t>(ft_dice_roll(1, static_cast<int>(this->size())) - 1);
    ElementType* elem = (*this)[index];
    this->release_at(index);
    return (elem);
}

template<typename ElementType>
ElementType *deck<ElementType>::drawTopElement()
{
    if (this->empty())
	{
		ft_errno = DECK_EMPTY;
		this->setError(DECK_EMPTY);
		return (ft_nullptr);
	}
	size_t index = this->size() - 1;
    ElementType* elem = (*this)[index];
	this->release_at(index);
    return (elem);
}

template<typename ElementType>
void deck<ElementType>::shuffle()
{
    if (this->empty())
	{
		ft_errno = DECK_EMPTY;
        this->setError(DECK_EMPTY);
		return ;
	}
	size_t index = this->size - 1;
    while (index > 0)
    {
        size_t randomIndex = static_cast<size_t>(ft_dice_roll(1, static_cast<int>(index + 1)) - 1);
        ft_swap((*this)[index], (*this)[randomIndex]);
		index--;
    }
	return ;
}

#endif
