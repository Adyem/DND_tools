#ifndef SHARED_PTR_HPP
# define SHARED_PTR_HPP

template <typename T>
class SharedPtr	
{
	private:
		T* ptr;
		int* ref_count;

	public:
		explicit SharedPtr(T* p = nullptr);
		SharedPtr(const SharedPtr<T>& other);
		~SharedPtr();
		
		SharedPtr<T>& operator=(const SharedPtr<T>& other);
		
		T& operator*() const;
		T* operator->() const;
		
		int use_count() const;
};

#include "shared_ptr.hpp"

template <typename T>
SharedPtr<T>::SharedPtr(T* p)
    : ptr(p), ref_count(new int(1))
{
	return ;
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
    : ptr(other.ptr), ref_count(other.ref_count)
{
    (*ref_count)++;
    return ;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    if (--(*ref_count) == 0)
    {
        delete ptr;
        delete ref_count;
    }
    return ;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
    if (this != &other) {
        if (--(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
        ptr = other.ptr;
        ref_count = other.ref_count;
        (*ref_count)++;
    }
    return (*this);
}

template <typename T>
T& SharedPtr<T>::operator*() const
{
    return (*ptr);
}

template <typename T>
T* SharedPtr<T>::operator->() const
{
    return (ptr);
}

template <typename T>
int SharedPtr<T>::use_count() const
{
    return (*ref_count);
}

#endif
