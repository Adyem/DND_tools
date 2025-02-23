#ifndef DECK_HPP
#define DECK_HPP

#include "../Template/vector.hpp"
#include <cstdlib>
#include <ctime>

template<typename ElementType>
class deck : public ft_vector<ElementType>
{
public:
    deck();
    
    ElementType getRandomElement();
    ElementType popRandomElement();
};

template<typename ElementType>
deck<ElementType>::deck() : ft_vector<ElementType>()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

template<typename ElementType>
ElementType deck<ElementType>::getRandomElement()
{
    if (this->empty())
	{
        this->setError(VECTOR_INVALID_OPERATION);
		return (ft_nullptr);
	}
    size_t index = std::rand() % this->size();
    return ((*this)[index]);
}

template<typename ElementType>
ElementType deck<ElementType>::popRandomElement()
{
    if (this->empty())
	{
		this->setError(VECTOR_INVALID_OPERATION);
		return (ft_nullptr);
	}
    size_t index = std::rand() % this->size();
    ElementType elem = (*this)[index];
    this->erase(this->begin() + index);
    return (elem);
}

#endif
