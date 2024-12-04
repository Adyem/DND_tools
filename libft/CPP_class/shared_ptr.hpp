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
		SharedPtr(SharedPtr<ManagedType>&& other) noexcept;
		SharedPtr<ManagedType>& operator=(SharedPtr<ManagedType>&& other) noexcept;
    	SharedPtr<ManagedType>& operator=(const SharedPtr<ManagedType>& other);
    	ManagedType& operator*();
    	const ManagedType& operator*() const;
    	ManagedType* operator->();
    	const ManagedType* operator->() const;
    	ManagedType& operator[](size_t index);
    	const ManagedType& operator[](size_t index) const;
    	int use_count() const;
    	bool hasError() const;
		void set_error(int error);
    	int getErrorCode() const;
    	const char* errorMessage() const;
    	ManagedType* get();
    	const ManagedType* get() const;
    	bool unique() const;
		explicit operator bool() const noexcept;
    	void reset(ManagedType* pointer = ft_nullptr, size_t size = 1,
			bool arrayType = false, bool critical = false);
    	void swap(SharedPtr<ManagedType>& other);
		void remove(size_t index);
		void add(const ManagedType& element);
};

template <typename ManagedType>
SharedPtr<ManagedType>::SharedPtr(ManagedType* pointer, size_t size, bool arrayType, bool critical)
    : managedPointer(pointer),
      referenceCount(static_cast<int*>(cma_malloc(sizeof(int), critical))),
      arraySize(size), isArrayType(arrayType), isCritical(critical),
	  errorCode(ER_SUCCESS)
{
    if (referenceCount)
        *referenceCount = 1;
    else
    {
		set_error(SHARED_PTR_ALLOCATION_FAILED);
        if (managedPointer)
        {
            if (isArrayType)
            {
				size_t index = 0;
                while (index < arraySize)
				{
                    managedPointer[index].~ManagedType();
					index++;
				}
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
    : managedPointer(other.managedPointer), referenceCount(other.referenceCount),
      arraySize(other.arraySize), isArrayType(other.isArrayType),
      isCritical(other.isCritical), errorCode(other.errorCode)
{
	if (referenceCount && errorCode == ER_SUCCESS)
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
					size_t index = 0;
                    while (index < arraySize)
					{
                        managedPointer[index].~ManagedType();
						index++;
					}
                }
                else
                    managedPointer->~ManagedType();
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
SharedPtr<ManagedType>::SharedPtr(SharedPtr<ManagedType>&& other) noexcept
    : managedPointer(other.managedPointer),
      referenceCount(other.referenceCount),
      arraySize(other.arraySize),
      isArrayType(other.isArrayType),
      isCritical(other.isCritical),
      errorCode(other.errorCode)
{
    other.managedPointer = ft_nullptr;
    other.referenceCount = ft_nullptr;
}

template <typename ManagedType>
SharedPtr<ManagedType>& SharedPtr<ManagedType>::operator=(SharedPtr<ManagedType>&& other) noexcept
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
        other.managedPointer = ft_nullptr;
        other.referenceCount = ft_nullptr;
    }
    return *this;
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
        if (referenceCount && errorCode == ER_SUCCESS)
            (*referenceCount)++;
    }
    return (*this);
}

template <typename ManagedType>
const ManagedType& SharedPtr<ManagedType>::operator*() const
{
    if (!managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        static ManagedType defaultInstance;
        return defaultInstance;
    }
    return (*managedPointer);
}

template <typename ManagedType>
const ManagedType* SharedPtr<ManagedType>::operator->() const
{
    if (!managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        return (ft_nullptr);
    }
    return (managedPointer);
}

template <typename ManagedType>
const ManagedType& SharedPtr<ManagedType>::operator[](size_t index) const
{
    if (!isArrayType)
    {
        this->set_error(SHARED_PTR_INVALID_OPERATION);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    if (!managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    if (index >= arraySize)
    {
        this->set_error(SHARED_PTR_OUT_OF_BOUNDS);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    return (managedPointer[index]);
}

template <typename ManagedType>
ManagedType* SharedPtr<ManagedType>::get()
{
    return (managedPointer);
}

template <typename ManagedType>
ManagedType& SharedPtr<ManagedType>::operator*()
{
    if (!managedPointer)
    {
		this->set_error(SHARED_PTR_NULL_PTR);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    return (*managedPointer);
}

template <typename ManagedType>
ManagedType* SharedPtr<ManagedType>::operator->()
{
    if (!managedPointer)
    {
		this->set_error(SHARED_PTR_NULL_PTR);
        return ft_nullptr;
    }
    return (managedPointer);
}

template <typename ManagedType>
ManagedType& SharedPtr<ManagedType>::operator[](size_t index)
{
    if (!isArrayType)
    {
		this->set_error(SHARED_PTR_INVALID_OPERATION);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    if (!managedPointer)
    {
		this->set_error(SHARED_PTR_NULL_PTR);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    if (index >= arraySize)
    {
		this->set_error(SHARED_PTR_OUT_OF_BOUNDS);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    return (managedPointer[index]);
}

template <typename ManagedType>
int SharedPtr<ManagedType>::use_count() const
{
    if (referenceCount && errorCode == ER_SUCCESS)
        return (*referenceCount);
    return (0);
}

template <typename ManagedType>
bool SharedPtr<ManagedType>::hasError() const
{
    return (errorCode != ER_SUCCESS);
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
const ManagedType* SharedPtr<ManagedType>::get() const
{
    return (managedPointer);
}

template <typename ManagedType>
bool SharedPtr<ManagedType>::unique() const
{
    return (use_count() == 1);
}

template <typename ManagedType>
void SharedPtr<ManagedType>::set_error(int error)
{
	ft_errno = error;
	this->errorCode = error;
	return ;
}

template <typename ManagedType>
void SharedPtr<ManagedType>::reset(ManagedType* pointer, size_t size, bool arrayType, bool critical)
{
    release();
    managedPointer = pointer;
    arraySize = size;
    isArrayType = arrayType;
    isCritical = critical;
    errorCode = ER_SUCCESS;
    referenceCount = static_cast<int*>(cma_malloc(sizeof(int), critical));
    if (referenceCount)
        *referenceCount = 1;
    else
    {
		this->set_error(SHARED_PTR_ALLOCATION_FAILED);
        if (managedPointer)
        {
            if (isArrayType)
            {
				size_t index = 0;
                while (index < arraySize)
				{
                    managedPointer[index].~ManagedType();
					index++;
				}
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
SharedPtr<ManagedType>::operator bool() const noexcept
{
    return (managedPointer != ft_nullptr);
}

template <typename ManagedType>
void SharedPtr<ManagedType>::add(const ManagedType& element)
{
    if (!isArrayType)
    {
        this->set_error(SHARED_PTR_INVALID_OPERATION);
        return ;
    }
    if (!managedPointer)
    {
        managedPointer = static_cast<ManagedType*>(cma_malloc(sizeof(ManagedType), isCritical));
        if (!managedPointer)
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
            return ;
        }
        new (managedPointer) ManagedType(element);
        arraySize = 1;
        return ;
    }
	for (size_t i = 0; i < arraySize; ++i)
    {
        if (&managedPointer[i] == &element)
        {
			this->set_error(SHARED_PTR_ELEMENT_ALREADDY_ADDED);
            return ;
        }
    }
    ManagedType* newArray = static_cast<ManagedType*>(cma_realloc(managedPointer,
				sizeof(ManagedType) * (arraySize + 1), isCritical));
    if (!newArray)
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
        return ;
    }
    managedPointer = newArray;
    new (&managedPointer[arraySize]) ManagedType(element);
    arraySize += 1;
	return ;
}

template <typename ManagedType>
void SharedPtr<ManagedType>::remove(size_t index)
{
    if (!isArrayType)
    {
        this->set_error(SHARED_PTR_INVALID_OPERATION);
        return ;
    }
    if (!managedPointer || index >= arraySize)
    {
        this->set_error(SHARED_PTR_OUT_OF_BOUNDS);
        return ;
    }
    managedPointer[index].~ManagedType();
    for (size_t i = index; i < arraySize - 1; ++i)
    {
        new (&managedPointer[i]) ManagedType(managedPointer[i + 1]);
        managedPointer[i + 1].~ManagedType();
    }
    arraySize -= 1;
    if (arraySize == 0)
    {
        cma_free(managedPointer);
        managedPointer = ft_nullptr;
        release();
    }
    else
    {
        ManagedType* newArray = static_cast<ManagedType*>(cma_realloc(managedPointer,
					sizeof(ManagedType) * arraySize, isCritical));
        if (!newArray)
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
            return ;
        }
        managedPointer = newArray;
    }
	return ;
}

#endif
