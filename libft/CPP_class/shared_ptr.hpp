#ifndef SHARED_PTR_HPP
# define SHARED_PTR_HPP

#include "../CMA/CMA.hpp"

template <typename T>
class SharedPtr
{
	private:
	    T		*ptr;
	    int		*ref_count;
	    bool	criticality;
		bool	errorFlag;

	public:
	    explicit SharedPtr(T* p = nullptr, bool crit = false);
	    SharedPtr(const SharedPtr<T>& other);
	    ~SharedPtr();
	    SharedPtr<T>& operator=(const SharedPtr<T>& other);
	    T& operator*() const;
	    T* operator->() const;
	    int use_count() const;
		bool hasError() const;
};

template <typename T>
SharedPtr<T>::SharedPtr(T* p, bool crit)
    : ptr(p), ref_count(static_cast<int*>(cma_malloc(sizeof(int), crit))),
      criticality(crit), errorFlag(false)
{
	if (ref_count)
        *ref_count = 1;
	else
	{
        errorFlag = true;
        if (ptr)
		{
            ptr->~T();
            cma_free(ptr);
            ptr = nullptr;
        }
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
    : ptr(other.ptr), ref_count(other.ref_count),
      criticality(other.criticality), errorFlag(other.errorFlag)
{
    if (ref_count && !errorFlag)
        (*ref_count)++;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    if (ref_count && --(*ref_count) == 0)
	{
        if (ptr)
		{
            ptr->~T();
            cma_free(ptr);
        }
        cma_free(ref_count);
    }
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
    if (this != &other)
	{
        if (ref_count && --(*ref_count) == 0)
		{
            if (ptr)
			{
                ptr->~T();
                cma_free(ptr);
            }
            cma_free(ref_count);
        }
        ptr = other.ptr;
        ref_count = other.ref_count;
        criticality = other.criticality;
        errorFlag = other.errorFlag;
        if (ref_count && !errorFlag)
            (*ref_count)++;
    }
    return *this;
}

template <typename T>
T& SharedPtr<T>::operator*() const
{
    return *ptr;
}

template <typename T>
T* SharedPtr<T>::operator->() const
{
    return ptr;
}

template <typename T>
int SharedPtr<T>::use_count() const
{
    return (ref_count && !errorFlag) ? *ref_count : 0;
}

template <typename T>
bool SharedPtr<T>::hasError() const
{
    return errorFlag;
}

#endif
