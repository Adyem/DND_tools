#ifndef FT_VECTOR_H
#define FT_VECTOR_H

#include "../CPP_class/nullptr.hpp"
#include "../Errno/errno.hpp"
#include "../CMA/CMA.hpp"
#include "constructor.hpp"
#include <cstddef>
#include <utility>

template <typename ElementType>
class ft_vector
{
	private:
    	ElementType	*_data;
    	size_t		_size;
    	size_t		_capacity;
    	bool		_errorCode;

    	void	destroy_elements(size_t from, size_t to);

	protected:
		void	setError(int errorCode);
		ElementType release_at(size_t index);

	public:
    	using iterator = ElementType*;
    	using const_iterator = const ElementType*;

    	ft_vector(size_t initial_capacity = 0);
    	~ft_vector();

    	ft_vector(const ft_vector&) = delete;
    	ft_vector& operator=(const ft_vector&) = delete;

    	ft_vector(ft_vector&& other) noexcept;
    	ft_vector& operator=(ft_vector&& other) noexcept;

    	size_t size() const;
    	size_t capacity() const;
    	int getError() const;

    	void push_back(const ElementType &value);
    	void push_back(ElementType &&value);
    	void pop_back();

    	ElementType& operator[](size_t index);
    	const ElementType& operator[](size_t index) const;

    	void clear();
    	void reserve(size_t new_capacity);
    	void resize(size_t new_size, const ElementType& value = ElementType());

    	iterator insert(iterator pos, const ElementType& value);
    	iterator erase(iterator pos);
    	iterator begin();
    	const_iterator begin() const;
    	iterator end();
    	const_iterator end() const;
};

template <typename ElementType>
ft_vector<ElementType>::ft_vector(size_t initial_capacity)
    : _data(nullptr), _size(0), _capacity(0), _errorCode(false)
{
    if (initial_capacity > 0)
    {
        this->_data = static_cast<ElementType*>
			(cma_malloc(initial_capacity * sizeof(ElementType)));
        if (this->_data == ft_nullptr)
            this->setError(VECTOR_ALLOC_FAIL);
        else
            this->_capacity = initial_capacity;
    }
    return ;
}

template <typename ElementType>
ft_vector<ElementType>::~ft_vector()
{
    destroy_elements(0, this->_size);
    if (this->_data != nullptr)
        cma_free(this->_data);
    return ;
}

template <typename ElementType>
ft_vector<ElementType>::ft_vector(ft_vector<ElementType>&& other) noexcept
    : _data(other._data),
      _size(other._size),
      _capacity(other._capacity),
      _errorCode(other._errorCode)
{
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._errorCode = false;
}

template <typename ElementType>
ft_vector<ElementType>& ft_vector<ElementType>::operator=(ft_vector<ElementType>&& other) noexcept
{
    if (this != &other)
    {
        destroy_elements(0, this->_size);
        if (this->_data != nullptr)
            cma_free(this->_data);
        this->_data = other._data;
        this->_size = other._size;
        this->_capacity = other._capacity;
        this->_errorCode = other._errorCode;
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
        other._errorCode = false;
    }
    return (*this);
}

template <typename ElementType>
void ft_vector<ElementType>::destroy_elements(size_t from, size_t to)
{
    for (size_t index = from; index < to; index++)
        destroy_at(&this->_data[index]);
    return ;
}

template <typename ElementType>
size_t ft_vector<ElementType>::size() const
{
    return (this->_size);
}

template <typename ElementType>
size_t ft_vector<ElementType>::capacity() const
{
    return (this->_capacity);
}

template <typename ElementType>
void ft_vector<ElementType>::setError(int errorCode)
{
    this->_errorCode = true;
    ft_errno = errorCode;
    return ;
}

template <typename ElementType>
int ft_vector<ElementType>::getError() const
{
    return (this->_errorCode);
}

template <typename ElementType>
void ft_vector<ElementType>::push_back(const ElementType &value)
{
    if (this->_size >= this->_capacity)
    {
        size_t newCapacity;
        if (this->_capacity > 0)
            newCapacity = this->_capacity * 2;
        else
            newCapacity = 1;
        reserve(newCapacity);
        if (this->_errorCode)
            return ;
    }
    construct_at(&this->_data[this->_size], value);
    this->_size++;
	return ;
}

template <typename ElementType>
void ft_vector<ElementType>::push_back(ElementType &&value)
{
    if (this->_size >= this->_capacity)
    {
        size_t newCapacity;
        if (this->_capacity > 0)
            newCapacity = this->_capacity * 2;
        else
            newCapacity = 1;
        reserve(newCapacity);
        if (this->_errorCode)
            return ;
    }
    construct_at(&this->_data[this->_size], std::forward<ElementType>(value));
    this->_size++;
	return ;
}

template <typename ElementType>
void ft_vector<ElementType>::pop_back()
{
    if (this->_size > 0)
    {
        destroy_at(&this->_data[this->_size - 1]);
        this->_size--;
    }
    else
        this->setError(VECTOR_INVALID_OPERATION);
    return ;
}

template <typename ElementType>
ElementType& ft_vector<ElementType>::operator[](size_t index)
{
    if (index >= this->_size)
    {
        this->setError(VECTOR_OUT_OF_BOUNDS);
        static ElementType defaultInstance = ElementType();
        return (defaultInstance);
    }
    return (this->_data[index]);
}

template <typename ElementType>
const ElementType& ft_vector<ElementType>::operator[](size_t index) const
{
    if (index >= this->_size)
    {
        const_cast<ft_vector<ElementType>*>(this)->setError(VECTOR_OUT_OF_BOUNDS);
        static const ElementType defaultInstance = ElementType();
        return (defaultInstance);
    }
    return (this->_data[index]);
}

template <typename ElementType>
void ft_vector<ElementType>::clear()
{
    destroy_elements(0, this->_size);
    this->_size = 0;
    return ;
}

template <typename ElementType>
void ft_vector<ElementType>::reserve(size_t new_capacity)
{
    if (new_capacity > this->_capacity)
    {
        ElementType* new_data = static_cast<ElementType*>(cma_realloc(this->_data,
                    new_capacity * sizeof(ElementType)));
        if (new_data == nullptr)
        {
            this->setError(VECTOR_ALLOC_FAIL);
            return ;
        }
        this->_data = new_data;
        this->_capacity = new_capacity;
    }
    return ;
}

template <typename ElementType>
void ft_vector<ElementType>::resize(size_t new_size, const ElementType& value)
{
    if (new_size < this->_size)
        destroy_elements(new_size, this->_size);
    else if (new_size > this->_size)
    {
        reserve(new_size);
        if (this->_errorCode)
            return ;
        for (size_t index = this->_size; index < new_size; index++)
            construct_at(&this->_data[index], value);
    }
    this->_size = new_size;
    return ;
}

template <typename ElementType>
typename ft_vector<ElementType>::iterator ft_vector<ElementType>::insert(iterator pos, const ElementType& value)
{
    size_t index = pos - this->_data;
    if (index > this->_size)
        return (end());
    if (this->_size >= this->_capacity)
    {
        size_t new_capacity;
        if (this->_capacity > 0)
            new_capacity = this->_capacity * 2;
        else
            new_capacity = 1;
        reserve(new_capacity);
        if (this->_errorCode)
            return (end());
        pos = this->_data + index;
    }
    size_t i = this->_size;
    while (i > index)
    {
        construct_at(&this->_data[i], this->_data[i - 1]);
        destroy_at(&this->_data[i - 1]);
        i--;
    }
    construct_at(&this->_data[index], value);
    this->_size++;
    return (&this->_data[index]);
}

template <typename ElementType>
typename ft_vector<ElementType>::iterator ft_vector<ElementType>::erase(iterator pos)
{
    size_t index = pos - this->_data; 
    if (index >= this->_size)
    {
        this->setError(VECTOR_INVALID_PTR);
        return (end()); 
    }
    destroy_at(&this->_data[index]);
    for (size_t i = index; i < this->_size - 1; i++)
    {
        construct_at(&this->_data[i], this->_data[i + 1]);
        destroy_at(&this->_data[i + 1]);
    }
    --this->_size;
    if (index == this->_size)
        return (end());
    return (&this->_data[index]);
}

template <typename ElementType>
ElementType ft_vector<ElementType>::release_at(size_t index)
{
    if (index >= this->_size)
	{
        this->setError(VECTOR_INVALID_PTR);
        return ElementType();
    }
    ElementType detached = std::move(this->_data[index]);
    for (size_t i = index; i < this->_size - 1; i++)
        this->_data[i] = std::move(this->_data[i + 1]);
    --this->_size;
    return detached;
}

template <typename ElementType>
typename ft_vector<ElementType>::iterator ft_vector<ElementType>::begin()
{
    return (this->_data);
}

template <typename ElementType>
typename ft_vector<ElementType>::const_iterator ft_vector<ElementType>::begin() const
{
    return (this->_data);
}

template <typename ElementType>
typename ft_vector<ElementType>::iterator ft_vector<ElementType>::end()
{
    return (this->_data + this->_size);
}

template <typename ElementType>
typename ft_vector<ElementType>::const_iterator ft_vector<ElementType>::end() const
{
    return (this->_data + this->_size);
}

#endif
