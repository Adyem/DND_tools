#ifndef SHARED_PTR_HPP
# define SHARED_PTR_HPP

#include "../CMA/CMA.hpp"
#include "nullptr.hpp"
#include <cstddef>

#define SHARED_PTR_NO_ERROR 0
#define SHARED_PTR_NULL_PTR 1
#define SHARED_PTR_OUT_OF_BOUNDS 2
#define SHARED_PTR_ALLOCATION_FAILED 3
#define SHARED_PTR_INVALID_OPERATION 4

template <typename ManagedType>
class SharedPtr
{
    private:
        ManagedType   *managedPtr;
        int           *referenceCount;
        size_t        arraySize;
        bool          isArrayType;
        bool          isCritical;
        int           errorCode;

    public:
        explicit SharedPtr(ManagedType* ptr = ft_nullptr, size_t size = 1, bool arrayType = false,
                bool critical = false);
        SharedPtr(const SharedPtr<ManagedType>& other);
        ~SharedPtr();
        SharedPtr<ManagedType>& operator=(const SharedPtr<ManagedType>& other);
        ManagedType& operator*() const;
        ManagedType* operator->() const;
        ManagedType& operator[](size_t index) const;
        int use_count() const;
        bool hasError() const;
        int getErrorCode() const;
        const char* errorMessage() const;
};

template <typename ManagedType>
SharedPtr<ManagedType>::SharedPtr(ManagedType* ptr, size_t size, bool arrayType, bool critical)
    : managedPtr(ptr), referenceCount(static_cast<int*>(cma_malloc(sizeof(int), critical))),
      arraySize(size), isArrayType(arrayType), isCritical(critical), errorCode(SHARED_PTR_NO_ERROR)
{
    if (referenceCount)
        *referenceCount = 1;
    else
    {
        if (!managedPtr)
        {
            errorCode = SHARED_PTR_ALLOCATION_FAILED;
            return;
        }
        else
        {
            if (isArrayType)
            {
                for (size_t i = 0; i < arraySize; ++i)
                    managedPtr[i].~ManagedType();
            }
            else
                managedPtr->~ManagedType();
            cma_free(managedPtr);
            managedPtr = ft_nullptr;
            errorCode = SHARED_PTR_ALLOCATION_FAILED;
        }
    }
	return ;
}

template <typename ManagedType>
SharedPtr<ManagedType>::SharedPtr(const SharedPtr<ManagedType>& other)
    : managedPtr(other.managedPtr), referenceCount(other.referenceCount), arraySize(other.arraySize),
      isArrayType(other.isArrayType), isCritical(other.isCritical), errorCode(other.errorCode)
{
	if (referenceCount && errorCode == SHARED_PTR_NO_ERROR)
        (*referenceCount)++;
	return ;
}

template <typename ManagedType>
SharedPtr<ManagedType>::~SharedPtr()
{
    if (referenceCount && --(*referenceCount) == 0)
    {
        if (managedPtr)
        {
            if (isArrayType)
            {
                for (size_t i = 0; i < arraySize; ++i)
                    managedPtr[i].~ManagedType();
            }
            else
                managedPtr->~ManagedType();
            cma_free(managedPtr);
        }
        cma_free(referenceCount);
    }
	return ;
}

template <typename ManagedType>
SharedPtr<ManagedType>& SharedPtr<ManagedType>::operator=(const SharedPtr<ManagedType>& other)
{
    if (this != &other)
    {
        if (referenceCount && --(*referenceCount) == 0)
        {
            if (managedPtr)
            {
                if (isArrayType)
                {
                    for (size_t i = 0; i < arraySize; ++i)
                        managedPtr[i].~ManagedType();
                }
                else
                    managedPtr->~ManagedType();
                cma_free(managedPtr);
            }
            cma_free(referenceCount);
        }
        managedPtr = other.managedPtr;
        referenceCount = other.referenceCount;
        arraySize = other.arraySize;
        isArrayType = other.isArrayType;
        isCritical = other.isCritical;
        errorCode = other.errorCode;
        if (referenceCount && errorCode == SHARED_PTR_NO_ERROR)
            (*referenceCount)++;
    }
    return (*this);
}

template <typename ManagedType>
ManagedType& SharedPtr<ManagedType>::operator*() const
{
    if (!managedPtr)
    {
        const_cast<SharedPtr*>(this)->errorCode = SHARED_PTR_NULL_PTR;
        static ManagedType defaultInstance;
        return defaultInstance;
    }
    return (*managedPtr);
}

template <typename ManagedType>
ManagedType* SharedPtr<ManagedType>::operator->() const
{
    if (!managedPtr)
    {
        const_cast<SharedPtr*>(this)->errorCode = SHARED_PTR_NULL_PTR;
        return ft_nullptr;
    }
    return (managedPtr);
}

template <typename ManagedType>
ManagedType& SharedPtr<ManagedType>::operator[](size_t index) const
{
    if (!isArrayType)
    {
        const_cast<SharedPtr*>(this)->errorCode = SHARED_PTR_INVALID_OPERATION;
        static ManagedType defaultInstance;
        return defaultInstance;
    }
    if (!managedPtr)
    {
        const_cast<SharedPtr*>(this)->errorCode = SHARED_PTR_NULL_PTR;
        static ManagedType defaultInstance;
        return defaultInstance;
    }
    if (index >= arraySize)
    {
        const_cast<SharedPtr*>(this)->errorCode = SHARED_PTR_OUT_OF_BOUNDS;
        static ManagedType defaultInstance;
        return defaultInstance;
    }
    return (managedPtr[index]);
}

template <typename ManagedType>
int SharedPtr<ManagedType>::use_count() const
{
    if (referenceCount && errorCode == SHARED_PTR_NO_ERROR)
        return (*referenceCount);
    return 0;
}

template <typename ManagedType>
bool SharedPtr<ManagedType>::hasError() const
{
    return (errorCode != SHARED_PTR_NO_ERROR);
}

template <typename ManagedType>
int SharedPtr<ManagedType>::getErrorCode() const
{
    return (errorCode);
}

template <typename ManagedType>
const char* SharedPtr<ManagedType>::errorMessage() const
{
    switch (errorCode)
    {
        case SHARED_PTR_NO_ERROR:
            return "No error";
        case SHARED_PTR_NULL_PTR:
            return "Null pointer dereference";
        case SHARED_PTR_OUT_OF_BOUNDS:
            return "Array index out of bounds";
        case SHARED_PTR_ALLOCATION_FAILED:
            return "Memory allocation failed";
        case SHARED_PTR_INVALID_OPERATION:
            return "Invalid operation";
        default:
            return "Unknown error";
    }
}

#endif
