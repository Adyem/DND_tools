#ifndef VECTOR_H
# define VECTOR_H

#include "../CMA/CMA.hpp"
#include <cstddef>

template <typename T>
class Vector {
	private:
    	T* data;
    	size_t size_;
    	size_t capacity_;
    	bool error_flag;
    	bool critical;

	public:
	    Vector(size_t initial_capacity = 0, bool criticality = false);
	    ~Vector();
	    Vector(const Vector&) = delete;
    	Vector& operator=(const Vector&) = delete;
    	size_t size() const;
    	size_t capacity() const;
    	bool has_error() const;
    	void push_back(const T& value);
    	void pop_back();
    	T& operator[](size_t index);
    	const T& operator[](size_t index) const;
    	void clear();
    	void reserve(size_t new_capacity);
};

template <typename T>
Vector<T>::Vector(size_t initial_capacity, bool criticality)
    : data(nullptr), size_(0), capacity_(0), error_flag(false), critical(criticality)
{
    if (initial_capacity > 0)
	{
        data = static_cast<T*>(cma_malloc(initial_capacity * sizeof(T), critical));
        if (data == nullptr)
            error_flag = true;
        else
            capacity_ = initial_capacity;
    }
	return ;
}

template <typename T>
Vector<T>::~Vector()
{
    for (size_t i = 0; i < size_; ++i)
        data[i].~T();
    if (data != nullptr)
        cma_free(data);
	return ;
}

template <typename T>
size_t Vector<T>::size() const
{
    return (size_);
}

template <typename T>
size_t Vector<T>::capacity() const
{
    return (capacity_);
}

template <typename T>
bool Vector<T>::has_error() const
{
    return (error_flag);
}

template <typename T>
void Vector<T>::push_back(const T& value)
{
    if (size_ >= capacity_)
	{
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* new_data = static_cast<T*>(cma_realloc(data, new_capacity * sizeof(T), critical));
        if (new_data == nullptr)
		{
            error_flag = true;
            return ;
        }
        data = new_data;
        capacity_ = new_capacity;
    }
    new (&data[size_]) T(value);
    size_++;
	return ;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (size_ > 0)
	{
        data[size_ - 1].~T();
        size_--;
    }
	return ;
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
    return (data[index]);
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
    return (data[index]);
}

template <typename T>
void Vector<T>::clear()
{
    for (size_t i = 0; i < size_; ++i)
        data[i].~T();
    size_ = 0;
	return ;
}

template <typename T>
void Vector<T>::reserve(size_t new_capacity)
{
    if (new_capacity > capacity_)
	{
        T* new_data = static_cast<T*>(cma_realloc(data, new_capacity * sizeof(T), critical));
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

#endif
