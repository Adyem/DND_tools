#ifndef VECTOR_H
#define VECTOR_H

#include "nullptr.hpp"
#include "../Errno/errno.hpp"
#include "../CMA/CMA.hpp"
#include <cstddef>

template <typename ElementType>
class Vector
{
	private:
	    ElementType	*_data;
    	size_t		_size;
   		size_t		_capacity;
    	bool		_errorCode;
    	bool		_critical;

    	void	destroy_elements(size_t from, size_t to);
		void	setError(int errorCode);

	public:
	    using iterator = ElementType*;
	    using const_iterator = const ElementType*;

	    Vector(size_t initial_capacity = 0, bool criticality = false);
	    ~Vector();
	    Vector(const Vector&) = delete;
	    Vector& operator=(const Vector&) = delete;

	    size_t size() const;
	    size_t capacity() const;
	    int getError() const;

	    void push_back(const ElementType& value);
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
Vector<ElementType>::Vector(size_t initial_capacity, bool criticality)
    : _data(nullptr), _size(0), _capacity(0), _errorCode(0), _critical(criticality)
{
    if (initial_capacity > 0)
    {
        this->_data = static_cast<ElementType*>(cma_malloc(initial_capacity * sizeof(ElementType),
					this->_critical));
        if (this->_data == ft_nullptr)
            this->setError(VECTOR_ALLOC_FAIL);
        else
            this->_capacity = initial_capacity;
    }
	return ;
}

template <typename ElementType>
Vector<ElementType>::~Vector()
{
    destroy_elements(0, this->_size);
	if (this->_data != nullptr)
        cma_free(this->_data);
	return ;
}

template <typename ElementType>
void Vector<ElementType>::destroy_elements(size_t from, size_t to)
{
	size_t index = from;
	while (index < to)
	{
        this->_data[index].~ElementType();
		index++;
	}
	return ;
}

template <typename ElementType>
size_t Vector<ElementType>::size() const
{
    return (this->_size);
}

template <typename ElementType>
size_t Vector<ElementType>::capacity() const
{
    return (this->_capacity);
}

template <typename ElementType>
void Vector<ElementType>::setError(int errorCode)
{
	this->_errorCode = errorCode;
	ft_errno = errorCode;
	return ;
}

template <typename ElementType>
int Vector<ElementType>::getError() const
{
    return (this->_errorCode);
}

template <typename ElementType>
void Vector<ElementType>::push_back(const ElementType& value)
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
            return;
    }
    new (&this->_data[this->_size]) ElementType(value);
    this->_size++;
    return;
}

template <typename ElementType>
void Vector<ElementType>::pop_back()
{
    if (this->_size > 0)
    {
        this->_data[this->_size - 1].~ElementType();
        this->_size--;
    }
    else
        this->setError(VECTOR_INVALID_OPERATION);
    return ;
}

template <typename ElementType>
ElementType& Vector<ElementType>::operator[](size_t index)
{
    if (index >= this->_size || index < 0)
    {
        this->setError(VECTOR_OUT_OF_BOUNDS);
        static ElementType defaultInstance = ElementType();
        return (defaultInstance);
    }
    return (this->_data[index]);
}

template <typename ElementType>
const ElementType& Vector<ElementType>::operator[](size_t index) const
{
    if (index >= this->_size || index < 0)
    {
        this->setError(VECTOR_OUT_OF_BOUNDS);
        static const ElementType defaultInstance = ElementType();
        return (defaultInstance);
    }
    return (this->_data[index]);
}


template <typename ElementType>
void Vector<ElementType>::clear()
{
    destroy_elements(0, this->_size);
    this->_size = 0;
	return ;
}

template <typename ElementType>
void Vector<ElementType>::reserve(size_t new_capacity)
{
    if (new_capacity > this->_capacity)
    {
        ElementType* new_data = static_cast<ElementType*>(cma_realloc(this->_data,
					new_capacity * sizeof(ElementType), this->_critical));
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
void Vector<ElementType>::resize(size_t new_size, const ElementType& value)
{
    if (new_size < this->_size)
        destroy_elements(new_size, this->_size);
    else if (new_size > this->_size)
    {
        reserve(new_size);
        if (this->_errorCode)
			return ;
		size_t index = this->_size;
        while (index < new_size)
		{
            new (&this->_data[index]) ElementType(value);
			index++;
		}
    }
    this->_size = new_size;
	return ;
}

template <typename ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::insert(iterator pos,
		const ElementType& value)
{
    size_t index = pos - this->_data;
    if (index > this->_size)
		return end();
    if (this->_size >= this->_capacity)
    {
        size_t new_capacity = 1;
        if (this->_capacity > 0)
        {
            new_capacity = this->_capacity * 2;
        }
        reserve(new_capacity);
        if (this->_errorCode)
			return end();
    }
	size_t i = this->_size;
	while (i > index)
	{
	    new (&this->_data[i]) ElementType(this->_data[i - 1]);
	    this->_data[i - 1].~ElementType();
	    --i;
	}
    new (&this->_data[index]) ElementType(value);
    this->_size++;
    return (&this->_data[index]);
}

template <typename ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::erase(iterator pos)
{
    size_t index = pos - this->_data; 
    if (index >= this->_size)
    {
        this->setError(VECTOR_INVALID_PTR);
        return (end()); 
    }
    this->_data[index].~ElementType();
    for (size_t i = index; i < this->_size - 1; ++i)
    {
        new (&this->_data[i]) ElementType(this->_data[i + 1]);
        this->_data[i + 1].~ElementType();
    }
    --this->_size;
    if (index == this->_size)
        return (end());
    return (&this->_data[index]);
}

template <typename ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::begin()
{
    return (this->_data);
}

template <typename ElementType>
typename Vector<ElementType>::const_iterator Vector<ElementType>::begin() const
{
    return (this->_data);
}

template <typename ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::end()
{
    return (this->_data + this->_size);
}

template <typename ElementType>
typename Vector<ElementType>::const_iterator Vector<ElementType>::end() const
{
    return (this->_data + this->_size);
}

#endif
