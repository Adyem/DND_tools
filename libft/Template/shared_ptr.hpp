#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include "../Errno/errno.hpp"
#include "../CMA/CMA.hpp"
#include "../CPP_class/nullptr.hpp"
#include "constructor.hpp"
#include <cstddef>
#include <utility>
#include <type_traits>

template <typename ManagedType>
class ft_sharedptr
{
	private:
	    ManagedType* managedPointer;
	    int* referenceCount;
	    size_t arraySize;
	    bool isArrayType;
	    bool isCritical;
	    mutable int errorCode;
	    void release();

	public:
		template <typename... Args>
    	ft_sharedptr(bool critical, Args&&... args);

	    ft_sharedptr();
	    ft_sharedptr(size_t size, bool critical = false);
	    ft_sharedptr(const ft_sharedptr<ManagedType>& other);
	    ~ft_sharedptr();
	    ft_sharedptr(ft_sharedptr<ManagedType>&& other) noexcept;
	    ft_sharedptr<ManagedType>& operator=(ft_sharedptr<ManagedType>&& other) noexcept;
	    ft_sharedptr<ManagedType>& operator=(const ft_sharedptr<ManagedType>& other);
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
	    void swap(ft_sharedptr<ManagedType>& other);
	    void remove(int index);
	    void add(const ManagedType& element);
};

template <typename ManagedType>
template <typename... Args>
ft_sharedptr<ManagedType>::ft_sharedptr(bool critical, Args&&... args)
    : managedPointer(nullptr),
      referenceCount(static_cast<int*>(cma_malloc(sizeof(int), critical))),
      arraySize(0),
      isArrayType(false),
      isCritical(critical),
      errorCode(ER_SUCCESS)
{
    if (!referenceCount)
    {
        set_error(SHARED_PTR_ALLOCATION_FAILED);
        return ;
    }
    *referenceCount = 1;
    managedPointer = static_cast<ManagedType*>(cma_malloc(sizeof(ManagedType), critical));
    if (!managedPointer)
    {
        set_error(SHARED_PTR_ALLOCATION_FAILED);
        cma_free(referenceCount);
        referenceCount = ft_nullptr;
        return ;
    }
    construct_at(managedPointer, std::forward<Args>(args)...);
	return ;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr()
    : managedPointer(nullptr),
      referenceCount(nullptr),
      arraySize(0),
      isArrayType(false),
      isCritical(false),
      errorCode(ER_SUCCESS)
{
    return ;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr(const ft_sharedptr<ManagedType>& other)
    : managedPointer(other.managedPointer), referenceCount(other.referenceCount),
      arraySize(other.arraySize), isArrayType(other.isArrayType),
      isCritical(other.isCritical), errorCode(other.errorCode)
{
    if (referenceCount && errorCode == ER_SUCCESS)
        (*referenceCount)++;
    return ;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::~ft_sharedptr()
{
    release();
    return ;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr(size_t size, bool critical)
    : managedPointer(nullptr),
      referenceCount(static_cast<int*>(cma_malloc(sizeof(int), critical))),
      arraySize(size),
      isArrayType(true),
      isCritical(critical),
      errorCode(ER_SUCCESS)
{
    if (referenceCount)
    {
        *referenceCount = 1;
        managedPointer = static_cast<ManagedType*>(cma_calloc(size, sizeof(ManagedType), critical));
        if (!managedPointer)
        {
            set_error(SHARED_PTR_ALLOCATION_FAILED);
            cma_free(referenceCount);
            referenceCount = ft_nullptr;
        }
        else
        {
            size_t index = 0;
            while (index < arraySize)
            {
                if constexpr (!std::is_trivially_constructible_v<ManagedType>)
                    new (&managedPointer[index]) ManagedType();
                index++;
            }
        }
    }
    else
        set_error(SHARED_PTR_ALLOCATION_FAILED);
    return ;
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::release()
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
ft_sharedptr<ManagedType>::ft_sharedptr(ft_sharedptr<ManagedType>&& other) noexcept
    : managedPointer(other.managedPointer),
      referenceCount(other.referenceCount),
      arraySize(other.arraySize),
      isArrayType(other.isArrayType),
      isCritical(other.isCritical),
      errorCode(other.errorCode)
{
    other.managedPointer = ft_nullptr;
    other.referenceCount = ft_nullptr;
    return ;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>& ft_sharedptr<ManagedType>::operator=(ft_sharedptr<ManagedType>&& other) noexcept
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
ft_sharedptr<ManagedType>& ft_sharedptr<ManagedType>::operator=(const ft_sharedptr<ManagedType>& other)
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
ManagedType& ft_sharedptr<ManagedType>::operator*()
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
const ManagedType& ft_sharedptr<ManagedType>::operator*() const
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
ManagedType* ft_sharedptr<ManagedType>::operator->()
{
    if (!managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        return ft_nullptr;
    }
    return (managedPointer);
}

template <typename ManagedType>
const ManagedType* ft_sharedptr<ManagedType>::operator->() const
{
    if (!managedPointer)
    {
        this->errorCode = SHARED_PTR_NULL_PTR;
        ft_errno = SHARED_PTR_NULL_PTR;
        return (ft_nullptr);
    }
    return (managedPointer);
}

template <typename ManagedType>
ManagedType& ft_sharedptr<ManagedType>::operator[](size_t index)
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
const ManagedType& ft_sharedptr<ManagedType>::operator[](size_t index) const
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
int ft_sharedptr<ManagedType>::use_count() const
{
    if (referenceCount && errorCode == ER_SUCCESS)
        return (*referenceCount);
    return (0);
}

template <typename ManagedType>
bool ft_sharedptr<ManagedType>::hasError() const
{
    return (errorCode != ER_SUCCESS);
}

template <typename ManagedType>
int ft_sharedptr<ManagedType>::getErrorCode() const
{
    return (errorCode);
}

template <typename ManagedType>
const char* ft_sharedptr<ManagedType>::errorMessage() const
{
    return (ft_strerror(this->errorCode));
}

template <typename ManagedType>
ManagedType* ft_sharedptr<ManagedType>::get()
{
    return (managedPointer);
}

template <typename ManagedType>
const ManagedType* ft_sharedptr<ManagedType>::get() const
{
    return (managedPointer);
}

template <typename ManagedType>
bool ft_sharedptr<ManagedType>::unique() const
{
    return (use_count() == 1);
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::set_error(int error)
{
    ft_errno = error;
    this->errorCode = error;
    return ;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::operator bool() const noexcept
{
    return (managedPointer != ft_nullptr);
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::reset(ManagedType* pointer, size_t size, bool arrayType, bool critical)
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
            {
                managedPointer->~ManagedType();
            }
            cma_free(managedPointer);
        }
        managedPointer = ft_nullptr;
    }
    return ;
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::swap(ft_sharedptr<ManagedType>& other)
{
    std::swap(managedPointer, other.managedPointer);
    std::swap(referenceCount, other.referenceCount);
    std::swap(arraySize, other.arraySize);
    std::swap(isArrayType, other.isArrayType);
    std::swap(isCritical, other.isCritical);
    std::swap(errorCode, other.errorCode);
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::add(const ManagedType& element)
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
    size_t i = 0;
    while (i < arraySize)
    {
        if (&managedPointer[i] == &element)
        {
            this->set_error(SHARED_PTR_ELEMENT_ALREADDY_ADDED);
            return ;
        }
        ++i;
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
void ft_sharedptr<ManagedType>::remove(int index)
{
    if (!isArrayType)
    {
        this->set_error(SHARED_PTR_INVALID_OPERATION);
        return ;
    }
    if (!managedPointer || static_cast<size_t>(index) >= arraySize || index < 0)
    {
        this->set_error(SHARED_PTR_OUT_OF_BOUNDS);
        return ;
    }
    managedPointer[index].~ManagedType();
    size_t i = index;
    while (i < arraySize - 1)
    {
        new (&managedPointer[i]) ManagedType(managedPointer[i + 1]);
        managedPointer[i + 1].~ManagedType();
        ++i;
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
