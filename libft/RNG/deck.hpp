#ifndef DECK_HPP
#define DECK_HPP

#include "../Template/shared_ptr.hpp"
#include "../Template/vector.hpp"
#include "dice_roll.hpp"
#include <climits>

template<typename ElementType>
class deck : public ft_vector<ft_sharedptr<ElementType>>
{
	public:
    	deck();
    
    	ft_sharedptr<ElementType> getRandomElement();
    	ft_sharedptr<ElementType> popRandomElement();
};

template<typename ElementType>
deck<ElementType>::deck() : ft_vector<ft_sharedptr<ElementType>>()
{
	return ;
}

template<typename ElementType>
ft_sharedptr<ElementType> deck<ElementType>::getRandomElement()
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
ft_sharedptr<ElementType> deck<ElementType>::popRandomElement()
{
    if (this->empty())
	{
		ft_errno = DECK_EMPTY;
		this->setError(DECK_EMPTY);
		return (ft_nullptr);
	}
    size_t index = static_cast<size_t>(ft_dice_roll(1, static_cast<int>(this->size())) - 1);
	ft_sharedptr<ElementType> elem = (*this)[index];
	if (elem.getErrorCode())
	{
		ft_errno = DECK_ALLOC_FAIL;
		this->setError(DECK_ALLOC_FAIL);
		return (ft_nullptr);
	}
    this->release_at(index);
    return (elem);
}

#endif
