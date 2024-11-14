#ifndef SHARED_PTR_HPP
# define SHARED_PTR_HPP

#include "../CMA/CMA.hpp"
#include "nullptr.hpp"

template <typename ManagedType>
class SharedPtr
{
    private:
        ManagedType   *ptr;
        int           *ref_count;
        bool          criticality;
        bool          errorFlag;

    public:
        explicit SharedPtr(ManagedType* p = ft_nullptr, bool crit = false);
        SharedPtr(const SharedPtr<ManagedType>& other);
        ~SharedPtr();
        SharedPtr<ManagedType>& operator=(const SharedPtr<ManagedType>& other);
        ManagedType& operator*() const;
        ManagedType* operator->() const;
        int use_count() const;
        bool hasError() const;
};
template <typename ManagedType>
SharedPtr<ManagedType>::SharedPtr(ManagedType* p, bool crit)
    : ptr(p), ref_count(static_cast<int*>(cma_malloc(sizeof(int), crit))),
      criticality(crit), errorFlag(false)
{
    if (ref_count)
        *ref_count = 1;
    else
    {
        if (!ptr)
        {
            errorFlag = true;
            return;
        }
        else if (ptr)
        {
            ptr->~ManagedType();
            cma_free(ptr);
            ptr = ft_nullptr;
            errorFlag = false;
        }
    }
    return;
}

template <typename ManagedType>
SharedPtr<ManagedType>::SharedPtr(const SharedPtr<ManagedType>& other)
    : ptr(other.ptr), ref_count(other.ref_count),
      criticality(other.criticality), errorFlag(other.errorFlag)
{
    if (ref_count && !errorFlag)
        (*ref_count)++;
    return;
}

template <typename ManagedType>
SharedPtr<ManagedType>::~SharedPtr()
{
    if (ref_count && --(*ref_count) == 0)
    {
        if (ptr)
        {
            ptr->~ManagedType();
            cma_free(ptr);
        }
        cma_free(ref_count);
    }
    return;
}

template <typename ManagedType>
SharedPtr<ManagedType>& SharedPtr<ManagedType>::operator=(const SharedPtr<ManagedType>& other)
{
    if (this != &other)
    {
        if (ref_count && --(*ref_count) == 0)
        {
            if (ptr)
            {
                ptr->~ManagedType();
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
    return (*this);
}

template <typename ManagedType>
ManagedType& SharedPtr<ManagedType>::operator*() const
{
    return (*ptr);
}

template <typename ManagedType>
ManagedType* SharedPtr<ManagedType>::operator->() const
{
    return (ptr);
}

template <typename ManagedType>
int SharedPtr<ManagedType>::use_count() const
{
    if (ref_count && !errorFlag)
        return (*ref_count);
    return (0);
}

template <typename ManagedType>
bool SharedPtr<ManagedType>::hasError() const
{
    return (errorFlag);
}

#endif
