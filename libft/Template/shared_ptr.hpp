#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include "../Errno/errno.hpp"
#include "../CMA/CMA.hpp"
#include "../CPP_class/nullptr.hpp"
#include "math.hpp"
#include "constructor.hpp"
#include <cstddef>
#include <utility>
#include <type_traits>

template <typename ManagedType>
class ft_sharedptr
{
	private:
    	ManagedType* _managedPointer;
    	int* _referenceCount;
    	size_t _arraySize;
    	bool _isArrayType;
    	mutable int _errorCode;

    	void release();

	public:
    	template <typename... Args,
    	          typename = std::enable_if_t<
    	              !(is_single_convertible_to_size_t<Args...>::value) &&
    	              std::is_constructible_v<ManagedType, Args&&...>
    	          >>
    	ft_sharedptr(Args&&... args);

    	ft_sharedptr(ManagedType* pointer, bool isArray = false, size_t arraySize = 1);

    	ft_sharedptr();
		ft_sharedptr(size_t size);
    	ft_sharedptr(const ft_sharedptr<ManagedType>& other);
    	ft_sharedptr(ft_sharedptr<ManagedType>&& other) noexcept;

    	~ft_sharedptr();

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
    	void set_error(int error) const;
    	int getErrorCode() const;
    	const char* errorMessage() const;
    	ManagedType* get();
    	const ManagedType* get() const;
    	bool unique() const;
    	explicit operator bool() const noexcept;

    	void reset(ManagedType* pointer = ft_nullptr, size_t size = 1, bool arrayType = false);
    	void swap(ft_sharedptr<ManagedType>& other);
    	void remove(int index);
    	void add(const ManagedType& element);
};

template <typename ManagedType>
template <typename... Args, typename>
ft_sharedptr<ManagedType>::ft_sharedptr(Args&&... args)
    : _managedPointer(nullptr),
      _referenceCount(static_cast<int*>(cma_malloc(sizeof(int)))),
      _arraySize(0),
      _isArrayType(false),
      _errorCode(ER_SUCCESS)
{
    if (!this->_referenceCount)
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
        return;
    }
    *(this->_referenceCount) = 1;
    this->_managedPointer = static_cast<ManagedType*>(cma_malloc(sizeof(ManagedType)));
    if (!this->_managedPointer)
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
        cma_free(this->_referenceCount);
        this->_referenceCount = ft_nullptr;
        return;
    }
    construct_at(this->_managedPointer, std::forward<Args>(args)...);
    return;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr(ManagedType* pointer, bool isArray, size_t arraySize)
    : _managedPointer(pointer),
      _referenceCount(pointer ? static_cast<int*>(cma_malloc(sizeof(int))) : nullptr),
      _arraySize(arraySize),
      _isArrayType(isArray),
      _errorCode(ER_SUCCESS)
{
    if (_referenceCount)
        *(_referenceCount) = 1;
    else if (pointer)
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
    return;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr()
    : _managedPointer(nullptr),
      _referenceCount(nullptr),
      _arraySize(0),
      _isArrayType(false),
      _errorCode(ER_SUCCESS)
{
    return;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr(size_t size)
    : _managedPointer(nullptr),
      _referenceCount(static_cast<int*>(cma_malloc(sizeof(int)))),
      _arraySize(size),
      _isArrayType(true),
      _errorCode(ER_SUCCESS)
{
    if (this->_referenceCount)
    {
        *(this->_referenceCount) = 1;
        this->_managedPointer = static_cast<ManagedType*>(cma_calloc(this->_arraySize, sizeof(ManagedType)));
        if (!this->_managedPointer)
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
            cma_free(this->_referenceCount);
            this->_referenceCount = ft_nullptr;
        }
        else
        {
            for (size_t index = 0; index < this->_arraySize; ++index)
            {
                if constexpr (!std::is_trivially_constructible_v<ManagedType>)
                    new (&this->_managedPointer[index]) ManagedType();
            }
        }
    }
    else
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
    }
    return;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr(const ft_sharedptr<ManagedType>& other)
    : _managedPointer(other._managedPointer),
      _referenceCount(other._referenceCount),
      _arraySize(other._arraySize),
      _isArrayType(other._isArrayType),
      _errorCode(other._errorCode)
{
    if (this->_referenceCount && this->_errorCode == ER_SUCCESS)
    {
        (*(this->_referenceCount))++;
    }
    return;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr(ft_sharedptr<ManagedType>&& other) noexcept
    : _managedPointer(other._managedPointer),
      _referenceCount(other._referenceCount),
      _arraySize(other._arraySize),
      _isArrayType(other._isArrayType),
      _errorCode(other._errorCode)
{
    other._managedPointer = ft_nullptr;
    other._referenceCount = ft_nullptr;
    other._arraySize = 0;
    other._isArrayType = false;
    other._errorCode = ER_SUCCESS;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::~ft_sharedptr()
{
    release();
    return;
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::release()
{
    if (this->_referenceCount)
    {
        (*(this->_referenceCount))--;
        if (*(this->_referenceCount) == 0)
        {
            if (this->_managedPointer)
            {
                if (this->_isArrayType)
                {
                    for (size_t index = 0; index < this->_arraySize; ++index)
                        this->_managedPointer[index].~ManagedType();
                }
                else
                {
                    this->_managedPointer->~ManagedType();
                }
                cma_free(this->_managedPointer);
            }
            cma_free(this->_referenceCount);
        }
    }
    this->_managedPointer = ft_nullptr;
    this->_referenceCount = ft_nullptr;
    return;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>& ft_sharedptr<ManagedType>::operator=(ft_sharedptr<ManagedType>&& other) noexcept
{
    if (this != &other)
    {
        this->release();
        this->_managedPointer = other._managedPointer;
        this->_referenceCount = other._referenceCount;
        this->_arraySize = other._arraySize;
        this->_isArrayType = other._isArrayType;
        this->_errorCode = other._errorCode;
        other._managedPointer = ft_nullptr;
        other._referenceCount = ft_nullptr;
        other._arraySize = 0;
        other._isArrayType = false;
        other._errorCode = ER_SUCCESS;
    }
    return (*this);
}

template <typename ManagedType>
ft_sharedptr<ManagedType>& ft_sharedptr<ManagedType>::operator=(const ft_sharedptr<ManagedType>& other)
{
    if (this != &other)
    {
        this->release();
        this->_managedPointer = other._managedPointer;
        this->_referenceCount = other._referenceCount;
        this->_arraySize = other._arraySize;
        this->_isArrayType = other._isArrayType;
        this->_errorCode = other._errorCode;
        if (this->_referenceCount && this->_errorCode == ER_SUCCESS)
            (*(this->_referenceCount))++;
    }
    return (*this);
}

template <typename ManagedType>
ManagedType& ft_sharedptr<ManagedType>::operator*()
{
    if (!this->_managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        static ManagedType defaultInstance;
        return defaultInstance;
    }
    return (*(this->_managedPointer));
}

template <typename ManagedType>
const ManagedType& ft_sharedptr<ManagedType>::operator*() const
{
    if (!this->_managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        static ManagedType defaultInstance;
        return defaultInstance;
    }
    return (*(this->_managedPointer));
}

template <typename ManagedType>
ManagedType* ft_sharedptr<ManagedType>::operator->()
{
    if (!this->_managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        return ft_nullptr;
    }
    return (this->_managedPointer);
}

template <typename ManagedType>
const ManagedType* ft_sharedptr<ManagedType>::operator->() const
{
    if (!this->_managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        return ft_nullptr;
    }
    return (this->_managedPointer);
}

template <typename ManagedType>
ManagedType& ft_sharedptr<ManagedType>::operator[](size_t index)
{
    if (!this->_isArrayType)
    {
        this->set_error(SHARED_PTR_INVALID_OPERATION);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    if (!this->_managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    if (index >= this->_arraySize)
    {
        this->set_error(SHARED_PTR_OUT_OF_BOUNDS);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    return (this->_managedPointer[index]);
}

template <typename ManagedType>
const ManagedType& ft_sharedptr<ManagedType>::operator[](size_t index) const
{
    if (!this->_isArrayType)
    {
        this->set_error(SHARED_PTR_INVALID_OPERATION);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    if (!this->_managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    if (index >= this->_arraySize)
    {
        this->set_error(SHARED_PTR_OUT_OF_BOUNDS);
        static ManagedType defaultInstance;
        return (defaultInstance);
    }
    return (this->_managedPointer[index]);
}

template <typename ManagedType>
int ft_sharedptr<ManagedType>::use_count() const
{
    if (this->_referenceCount && this->_errorCode == ER_SUCCESS)
    {
        return *(this->_referenceCount);
    }
    return 0;
}

template <typename ManagedType>
bool ft_sharedptr<ManagedType>::hasError() const
{
    return (this->_errorCode != ER_SUCCESS);
}

template <typename ManagedType>
int ft_sharedptr<ManagedType>::getErrorCode() const
{
    return (this->_errorCode);
}

template <typename ManagedType>
const char* ft_sharedptr<ManagedType>::errorMessage() const
{
    return (ft_strerror(this->_errorCode));
}

template <typename ManagedType>
ManagedType* ft_sharedptr<ManagedType>::get()
{
    return (this->_managedPointer);
}

template <typename ManagedType>
const ManagedType* ft_sharedptr<ManagedType>::get() const
{
    return (this->_managedPointer);
}

template <typename ManagedType>
bool ft_sharedptr<ManagedType>::unique() const
{
    return (this->use_count() == 1);
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::set_error(int error) const
{
    ft_errno = error;
    this->_errorCode = error;
    return;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::operator bool() const noexcept
{
    return (this->_managedPointer != ft_nullptr);
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::reset(ManagedType* pointer, size_t size, bool arrayType)
{
    this->release();
    this->_managedPointer = pointer;
    this->_arraySize = size;
    this->_isArrayType = arrayType;
    this->_errorCode = ER_SUCCESS;
    this->_referenceCount = static_cast<int*>(cma_malloc(sizeof(int)));
    if (this->_referenceCount)
    {
        *(this->_referenceCount) = 1;
    }
    else
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
        if (this->_managedPointer)
        {
            if (this->_isArrayType)
            {
                for (size_t index = 0; index < this->_arraySize; ++index)
                {
                    this->_managedPointer[index].~ManagedType();
                }
            }
            else
            {
                this->_managedPointer->~ManagedType();
            }
            cma_free(this->_managedPointer);
        }
        this->_managedPointer = ft_nullptr;
    }
    return;
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::swap(ft_sharedptr<ManagedType>& other)
{
    std::swap(this->_managedPointer, other._managedPointer);
    std::swap(this->_referenceCount, other._referenceCount);
    std::swap(this->_arraySize, other._arraySize);
    std::swap(this->_isArrayType, other._isArrayType);
    std::swap(this->_errorCode, other._errorCode);
    return;
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::add(const ManagedType& element)
{
    if (!this->_isArrayType)
    {
        this->set_error(SHARED_PTR_INVALID_OPERATION);
        return;
    }
    if (!this->_managedPointer)
    {
        this->_managedPointer = static_cast<ManagedType*>(cma_malloc(sizeof(ManagedType)));
        if (!this->_managedPointer)
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
            return;
        }
        new (this->_managedPointer) ManagedType(element);
        this->_arraySize = 1;
        return;
    }
    for (size_t i = 0; i < this->_arraySize; ++i)
    {
        if (&this->_managedPointer[i] == &element)
        {
            this->set_error(SHARED_PTR_ELEMENT_ALREADDY_ADDED);
            return;
        }
    }
    ManagedType* newArray = static_cast<ManagedType*>(cma_realloc(this->_managedPointer,
                sizeof(ManagedType) * (this->_arraySize + 1)));
    if (!newArray)
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
        return;
    }
    this->_managedPointer = newArray;
    new (&(this->_managedPointer[this->_arraySize])) ManagedType(element);
    this->_arraySize += 1;
    return;
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::remove(int index)
{
    if (!this->_isArrayType)
    {
        this->set_error(SHARED_PTR_INVALID_OPERATION);
        return;
    }
    if (!this->_managedPointer || static_cast<size_t>(index) >= this->_arraySize || index < 0)
    {
        this->set_error(SHARED_PTR_OUT_OF_BOUNDS);
        return;
    }
    this->_managedPointer[index].~ManagedType();
    for (size_t i = index; i < this->_arraySize - 1; ++i)
    {
        new (&this->_managedPointer[i]) ManagedType(this->_managedPointer[i + 1]);
        this->_managedPointer[i + 1].~ManagedType();
    }
    this->_arraySize -= 1;
    if (this->_arraySize == 0)
    {
        cma_free(this->_managedPointer);
        this->_managedPointer = ft_nullptr;
        this->release();
    }
    else
    {
        ManagedType* newArray = static_cast<ManagedType*>(cma_realloc(this->_managedPointer,
                    sizeof(ManagedType) * this->_arraySize));
        if (!newArray)
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
            return;
        }
        this->_managedPointer = newArray;
    }
    return;
}

#endif
