#ifndef VECTOR_H
#define VECTOR_H

#include "../CMA/CMA.hpp"
#include <cstddef>

template <typename ElementType>
class Vector
{
	private:
	    ElementType* data;
    	size_t size_;
   		size_t capacity_;
    	bool error_flag;
    	bool critical;

    	void destroy_elements(size_t from, size_t to);

	public:
	    using iterator = ElementType*;
	    using const_iterator = const ElementType*;

	    Vector(size_t initial_capacity = 0, bool criticality = false);
	    ~Vector();
	    Vector(const Vector&) = delete;
	    Vector& operator=(const Vector&) = delete;

	    size_t size() const;
	    size_t capacity() const;
	    bool has_error() const;

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
    : data(nullptr), size_(0), capacity_(0), error_flag(false), critical(criticality)
{
    if (initial_capacity > 0)
    {
        data = static_cast<ElementType*>(cma_malloc(initial_capacity * sizeof(ElementType), critical));
        if (data == nullptr)
            error_flag = true;
        else
            capacity_ = initial_capacity;
    }
	return ;
}

template <typename ElementType>
Vector<ElementType>::~Vector()
{
    destroy_elements(0, size_);
	if (data != nullptr)
        cma_free(data);
	return ;
}

template <typename ElementType>
void Vector<ElementType>::destroy_elements(size_t from, size_t to)
{
	for (size_t i = from; i < to; ++i)
        data[i].~ElementType();
	return ;
}

template <typename ElementType>
size_t Vector<ElementType>::size() const
{
    return (size_);
}

template <typename ElementType>
size_t Vector<ElementType>::capacity() const
{
    return (capacity_);
}

template <typename ElementType>
bool Vector<ElementType>::has_error() const
{
    return (error_flag);
}

template <typename ElementType>
void Vector<ElementType>::push_back(const ElementType& value)
{
    if (size_ >= capacity_)
    {
        reserve(capacity_ > 0 ? capacity_ * 2 : 1);
        if (error_flag) return;
    }
    new (&data[size_]) ElementType(value);
    size_++;
	return ;
}

template <typename ElementType>
void Vector<ElementType>::pop_back()
{
    if (size_ > 0)
    {
        data[size_ - 1].~ElementType();
        size_--;
    }
	return ;
}

template <typename ElementType>
ElementType& Vector<ElementType>::operator[](size_t index)
{
    return (data[index]);
}

template <typename ElementType>
const ElementType& Vector<ElementType>::operator[](size_t index) const
{
    return (data[index]);
}

template <typename ElementType>
void Vector<ElementType>::clear()
{
    destroy_elements(0, size_);
    size_ = 0;
	return ;
}

template <typename ElementType>
void Vector<ElementType>::reserve(size_t new_capacity)
{
    if (new_capacity > capacity_)
    {
        ElementType* new_data = static_cast<ElementType*>(cma_realloc(data, new_capacity * sizeof(ElementType), critical));
        if (new_data == nullptr)
        {
            error_flag = true;
            return ;
        }
        data = new_data;
        capacity_ = new_capacity;
    }
	return ;
}

template <typename ElementType>
void Vector<ElementType>::resize(size_t new_size, const ElementType& value)
{
    if (new_size < size_)
        destroy_elements(new_size, size_);
    else if (new_size > size_)
    {
        reserve(new_size);
        if (error_flag)
			return ;
        for (size_t i = size_; i < new_size; ++i)
            new (&data[i]) ElementType(value);
    }
    size_ = new_size;
	return ;
}

template <typename ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::insert(iterator pos, const ElementType& value)
{
    size_t index = pos - data;
    if (index > size_) return end();

    if (size_ >= capacity_)
    {
        reserve(capacity_ > 0 ? capacity_ * 2 : 1);
        if (error_flag) return end();
    }
    for (size_t i = size_; i > index; --i)
    {
        new (&data[i]) ElementType(data[i - 1]);
        data[i - 1].~ElementType();
    }
    new (&data[index]) ElementType(value);
    size_++;
    return (&data[index]);
}

template <typename ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::erase(iterator pos)
{
    size_t index = pos - data;
    if (index >= size_) return end();
    data[index].~ElementType();
    for (size_t i = index; i < size_ - 1; ++i)
    {
        new (&data[i]) ElementType(data[i + 1]);
        data[i + 1].~ElementType();
    }
    size_--;
    return (&data[index]);
}

template <typename ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::begin()
{
    return (data);
}

template <typename ElementType>
typename Vector<ElementType>::const_iterator Vector<ElementType>::begin() const
{
    return (data);
}

template <typename ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::end()
{
    return (data + size_);
}

template <typename ElementType>
typename Vector<ElementType>::const_iterator Vector<ElementType>::end() const
{
    return (data + size_);
}

#endif
