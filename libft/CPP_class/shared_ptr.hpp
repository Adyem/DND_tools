#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include "../Errno/errno.hpp"
#include "../CMA/CMA.hpp"
#include "nullptr.hpp"
#include <cstddef>

template <typename ManagedType>
class SharedPtr
{
	private:
	    ManagedType* managedPointer;
	    int* referenceCount;
	    size_t arraySize;
	    bool isArrayType;
	    bool isCritical;
	    int errorCode;
	    void release();

	public:
	    explicit SharedPtr(ManagedType* pointer = ft_nullptr, size_t size = 1,
			bool arrayType = false, bool critical = false);
	    SharedPtr(const SharedPtr<ManagedType>& other);
    	~SharedPtr();
    	SharedPtr<ManagedType>& operator=(const SharedPtr<ManagedType>& other);
    	ManagedType& operator*();
    	ManagedType* operator->();
    	ManagedType& operator[](size_t index);
    	int use_count() const;
    	bool hasError() const;
    	int getErrorCode() const;
    	const char* errorMessage() const;
    	ManagedType* get() const;
    	bool unique() const;
    	void reset(ManagedType* pointer = ft_nullptr, size_t size = 1,
			bool arrayType = false, bool critical = false);
    	void swap(SharedPtr<ManagedType>& other);
};

template <typename ManagedType>
SharedPtr<ManagedType>::SharedPtr(ManagedType* pointer, size_t size, bool arrayType, bool critical)
    : managedPointer(pointer),
      referenceCount(static_cast<int*>(cma_malloc(sizeof(int), critical))),
      arraySize(size),
      isArrayType(arrayType),
      isCritical(critical),
      errorCode(SHARED_PTR_NO_ERROR)
{
    if (referenceCount)
        *referenceCount = 1;
    else
    {
        errorCode = SHARED_PTR_ALLOCATION_FAILED;
		ft_errno = SHARED_PTR_ALLOCATION_FAILED;
        if (managedPointer)
        {
            if (isArrayType)
            {
                for (size_t i = 0; i < arraySize; ++i)
                    managedPointer[i].~ManagedType();
            }
            else
                managedPointer->~ManagedType();
            cma_free(managedPointer);
        }
        managedPointer = ft_nullptr;
    }
	return ;
}

template <typename ManagedType>
SharedPtr<ManagedType>::SharedPtr(const SharedPtr<ManagedType>& other)
    : managedPointer(other.managedPointer),
      referenceCount(other.referenceCount),
      arraySize(other.arraySize),
      isArrayType(other.isArrayType),
      isCritical(other.isCritical),
      errorCode(other.errorCode)
{
	if (referenceCount && errorCode == SHARED_PTR_NO_ERROR)
        (*referenceCount)++;
	return ;
}

template <typename ManagedType>
SharedPtr<ManagedType>::~SharedPtr()
{
    release();
	return ;
}

template <typename ManagedType>
void SharedPtr<ManagedType>::release()
{
    if (referenceCount)
    {
        (*referenceCount)--;
        if (*referenceCount == 0)
        {
            if (managedPointer)
            {
                if (isArrayType)
                {
                    for (size_t i = 0; i < arraySize; ++i)
                        managedPointer[i].~ManagedType();
                }
                else
                {
                    managedPointer->~ManagedType();
                }
                cma_free(managedPointer);
            }
            cma_free(referenceCount);
        }
    }
    managedPointer = ft_nullptr;
    referenceCount = ft_nullptr;
	return ;
}

template <typename ManagedType>
SharedPtr<ManagedType>& SharedPtr<ManagedType>::operator=(const SharedPtr<ManagedType>& other)
{
    if (this != &other)
    {
        release();
        managedPointer = other.managedPointer;
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
ManagedType& SharedPtr<ManagedType>::operator*()
{
    if (!managedPointer)
    {
        this->errorCode = SHARED_PTR_NULL_PTR;
		ft_errno = SHARED_PTR_NULL_PTR;
        static ManagedType defaultInstance;
        return defaultInstance;
    }
    return (*managedPointer);
}

template <typename ManagedType>
ManagedType* SharedPtr<ManagedType>::operator->()
{
    if (!managedPointer)
    {
        this->errorCode = SHARED_PTR_NULL_PTR;
		ft_errno = SHARED_PTR_NULL_PTR;
        return ft_nullptr;
    }
    return (managedPointer);
}

template <typename ManagedType>
ManagedType& SharedPtr<ManagedType>::operator[](size_t index)
{
    if (!isArrayType)
    {
        this->errorCode = SHARED_PTR_INVALID_OPERATION;
		ft_errno = SHARED_PTR_INVALID_OPERATION;
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    if (!managedPointer)
    {
        this->errorCode = SHARED_PTR_NULL_PTR;
		ft_errno = SHARED_PTR_NULL_PTR;
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    if (index >= arraySize)
    {
        this->errorCode = SHARED_PTR_OUT_OF_BOUNDS;
		ft_errno = SHARED_PTR_OUT_OF_BOUNDS;
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    return (managedPointer[index]);
}

template <typename ManagedType>
int SharedPtr<ManagedType>::use_count() const
{
    if (referenceCount && errorCode == SHARED_PTR_NO_ERROR)
        return (*referenceCount);
    return (0);
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
	return (ft_strerror(this->errorCode));
}

template <typename ManagedType>
ManagedType* SharedPtr<ManagedType>::get() const
{
    return (managedPointer);
}

template <typename ManagedType>
bool SharedPtr<ManagedType>::unique() const
{
    return (use_count() == 1);
}

template <typename ManagedType>
void SharedPtr<ManagedType>::reset(ManagedType* pointer, size_t size, bool arrayType, bool critical)
{
    release();
    managedPointer = pointer;
    arraySize = size;
    isArrayType = arrayType;
    isCritical = critical;
    errorCode = SHARED_PTR_NO_ERROR;
    referenceCount = static_cast<int*>(cma_malloc(sizeof(int), critical));
    if (referenceCount)
        *referenceCount = 1;
    else
    {
        errorCode = SHARED_PTR_ALLOCATION_FAILED;
		ft_errno = SHARED_PTR_ALLOCATION_FAILED;
        if (managedPointer)
        {
            if (isArrayType)
            {
                for (size_t i = 0; i < arraySize; ++i)
                    managedPointer[i].~ManagedType();
            }
            else
                managedPointer->~ManagedType();
            cma_free(managedPointer);
        }
        managedPointer = ft_nullptr;
    }
	return ;
}

#endif
