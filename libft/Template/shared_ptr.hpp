#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include "../Errno/errno.hpp"
#include "../CPP_class/nullptr.hpp"
#include "math.hpp"
#include <cstddef>
#include <utility>
#include <type_traits>
#include <cstdlib>
#include <new>

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
        template <typename U> friend class ft_sharedptr;

        template <typename... Args, typename = std::enable_if_t<
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

        template <typename Other, typename = std::enable_if_t<std::is_convertible_v<Other*,
				 ManagedType*>>>
        ft_sharedptr(const ft_sharedptr<Other>& other)
            : _managedPointer(other._managedPointer),
              _referenceCount(other._referenceCount),
              _arraySize(other._arraySize),
              _isArrayType(other._isArrayType),
              _errorCode(other._errorCode)
        {
            if (_referenceCount && _errorCode == ER_SUCCESS)
                ++(*_referenceCount);
        }

        template <typename Other, typename = std::enable_if_t<std::is_convertible_v<Other*,
				 ManagedType*>>>
        ft_sharedptr(ft_sharedptr<Other>&& other) noexcept
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
      _referenceCount(new (std::nothrow) int),
      _arraySize(0),
      _isArrayType(false),
      _errorCode(ER_SUCCESS)
{
    if (!_referenceCount)
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
        return;
    }
    *_referenceCount = 1;
    _managedPointer = new (std::nothrow) ManagedType(std::forward<Args>(args)...);
    if (!_managedPointer)
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
        delete _referenceCount;
        _referenceCount = ft_nullptr;
        return;
    }
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr(ManagedType* pointer, bool isArray, size_t arraySize)
    : _managedPointer(pointer),
      _referenceCount(pointer ? new (std::nothrow) int : nullptr),
      _arraySize(arraySize),
      _isArrayType(isArray),
      _errorCode(ER_SUCCESS)
{
    if (_referenceCount)
        *_referenceCount = 1;
    else if (pointer)
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr()
    : _managedPointer(nullptr),
      _referenceCount(nullptr),
      _arraySize(0),
      _isArrayType(false),
      _errorCode(ER_SUCCESS)
{
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr(size_t size)
    : _managedPointer(nullptr),
      _referenceCount(new (std::nothrow) int),
      _arraySize(size),
      _isArrayType(true),
      _errorCode(ER_SUCCESS)
{
    if (_referenceCount)
    {
        *_referenceCount = 1;
        _managedPointer = new (std::nothrow) ManagedType[size];
        if (!_managedPointer)
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
            delete _referenceCount;
            _referenceCount = ft_nullptr;
        }
    }
    else
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
    }
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::ft_sharedptr(const ft_sharedptr<ManagedType>& other)
    : _managedPointer(other._managedPointer),
      _referenceCount(other._referenceCount),
      _arraySize(other._arraySize),
      _isArrayType(other._isArrayType),
      _errorCode(other._errorCode)
{
    if (_referenceCount && _errorCode == ER_SUCCESS)
        ++(*_referenceCount);
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
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::release()
{
    if (_referenceCount)
    {
        --(*_referenceCount);
        if (*_referenceCount == 0)
        {
            if (_managedPointer)
            {
                if (_isArrayType)
                    delete[] _managedPointer;
                else
                    delete _managedPointer;
            }
            delete _referenceCount;
        }
    }
    _managedPointer = ft_nullptr;
    _referenceCount = ft_nullptr;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>& ft_sharedptr<ManagedType>::operator=(ft_sharedptr<ManagedType>&& other) noexcept
{
    if (this != &other)
    {
        release();
        _managedPointer = other._managedPointer;
        _referenceCount = other._referenceCount;
        _arraySize = other._arraySize;
        _isArrayType = other._isArrayType;
        _errorCode = other._errorCode;
        other._managedPointer = ft_nullptr;
        other._referenceCount = ft_nullptr;
        other._arraySize = 0;
        other._isArrayType = false;
        other._errorCode = ER_SUCCESS;
    }
    return *this;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>& ft_sharedptr<ManagedType>::operator=(const ft_sharedptr<ManagedType>& other)
{
    if (this != &other)
    {
        release();
        _managedPointer = other._managedPointer;
        _referenceCount = other._referenceCount;
        _arraySize = other._arraySize;
        _isArrayType = other._isArrayType;
        _errorCode = other._errorCode;
        if (_referenceCount && _errorCode == ER_SUCCESS)
            ++(*_referenceCount);
    }
    return *this;
}

template <typename ManagedType>
ManagedType& ft_sharedptr<ManagedType>::operator*()
{
    if (!_managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        if constexpr (!std::is_abstract_v<ManagedType>)
        {
            static ManagedType defaultInstance;
            return defaultInstance;
        }
        else
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
            static char dummy_buffer[sizeof(ManagedType)] = {0};
            return *reinterpret_cast<ManagedType*>(dummy_buffer);
        }
    }
    return *_managedPointer;
}

template <typename ManagedType>
const ManagedType& ft_sharedptr<ManagedType>::operator*() const
{
    if (!_managedPointer)
    {
        const_cast<ft_sharedptr<ManagedType>*>(this)->set_error(SHARED_PTR_NULL_PTR);
        if constexpr (!std::is_abstract_v<ManagedType>)
        {
            static ManagedType defaultInstance;
            return defaultInstance;
        }
        else
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
            static char dummy_buffer[sizeof(ManagedType)] = {0};
            return *reinterpret_cast<const ManagedType*>(dummy_buffer);
        }
    }
    return *_managedPointer;
}

template <typename ManagedType>
ManagedType* ft_sharedptr<ManagedType>::operator->()
{
    if (!_managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        return ft_nullptr;
    }
    return _managedPointer;
}

template <typename ManagedType>
const ManagedType* ft_sharedptr<ManagedType>::operator->() const
{
    if (!_managedPointer)
    {
        const_cast<ft_sharedptr<ManagedType>*>(this)->set_error(SHARED_PTR_NULL_PTR);
        return ft_nullptr;
    }
    return _managedPointer;
}

template <typename ManagedType>
ManagedType& ft_sharedptr<ManagedType>::operator[](size_t index)
{
    if (!_isArrayType)
    {
        this->set_error(SHARED_PTR_INVALID_OPERATION);
        if constexpr (!std::is_abstract_v<ManagedType>)
        {
            static ManagedType defaultInstance;
            return defaultInstance;
        }
        else
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
			return (ft_nullptr);
        }
    }
    if (!_managedPointer)
    {
        this->set_error(SHARED_PTR_NULL_PTR);
        if constexpr (!std::is_abstract_v<ManagedType>)
        {
            static ManagedType defaultInstance;
            return defaultInstance;
        }
        else
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
			return (ft_nullptr);
        }
    }
    if (index >= _arraySize)
    {
        this->set_error(SHARED_PTR_OUT_OF_BOUNDS);
        if constexpr (!std::is_abstract_v<ManagedType>)
        {
            static ManagedType defaultInstance;
            return defaultInstance;
        }
        else
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
			return (ft_nullptr);
        }
    }
    return _managedPointer[index];
}

template <typename ManagedType>
const ManagedType& ft_sharedptr<ManagedType>::operator[](size_t index) const
{
    if (!_isArrayType)
    {
        const_cast<ft_sharedptr<ManagedType>*>(this)->set_error(SHARED_PTR_INVALID_OPERATION);
        if constexpr (!std::is_abstract_v<ManagedType>)
        {
            static ManagedType defaultInstance;
            return defaultInstance;
        }
        else
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
			return (ft_nullptr);
        }
    }
    if (!_managedPointer)
    {
        const_cast<ft_sharedptr<ManagedType>*>(this)->set_error(SHARED_PTR_NULL_PTR);
        if constexpr (!std::is_abstract_v<ManagedType>)
        {
            static ManagedType defaultInstance;
            return defaultInstance;
        }
        else
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
			return (ft_nullptr);
        }
    }
    if (index >= _arraySize)
    {
        const_cast<ft_sharedptr<ManagedType>*>(this)->set_error(SHARED_PTR_OUT_OF_BOUNDS);
        if constexpr (!std::is_abstract_v<ManagedType>)
        {
            static ManagedType defaultInstance;
            return defaultInstance;
        }
        else
        {
            this->set_error(SHARED_PTR_ALLOCATION_FAILED);
			return (ft_nullptr);
        }
    }
    return _managedPointer[index];
}

template <typename ManagedType>
int ft_sharedptr<ManagedType>::use_count() const
{
    if (_referenceCount && _errorCode == ER_SUCCESS)
        return *_referenceCount;
    return 0;
}

template <typename ManagedType>
bool ft_sharedptr<ManagedType>::hasError() const
{
    return (_errorCode != ER_SUCCESS);
}

template <typename ManagedType>
int ft_sharedptr<ManagedType>::getErrorCode() const
{
    return _errorCode;
}

template <typename ManagedType>
const char* ft_sharedptr<ManagedType>::errorMessage() const
{
    return ft_strerror(_errorCode);
}

template <typename ManagedType>
ManagedType* ft_sharedptr<ManagedType>::get()
{
    return _managedPointer;
}

template <typename ManagedType>
const ManagedType* ft_sharedptr<ManagedType>::get() const
{
    return _managedPointer;
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
    _errorCode = error;
}

template <typename ManagedType>
ft_sharedptr<ManagedType>::operator bool() const noexcept
{
    return (_managedPointer != ft_nullptr);
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::reset(ManagedType* pointer, size_t size, bool arrayType)
{
    release();
    _managedPointer = pointer;
    _arraySize = size;
    _isArrayType = arrayType;
    _errorCode = ER_SUCCESS;
    _referenceCount = new (std::nothrow) int;
    if (_referenceCount)
    {
        *_referenceCount = 1;
    }
    else
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
        if (_managedPointer)
        {
            if (_isArrayType)
                delete[] _managedPointer;
            else
                delete _managedPointer;
        }
        _managedPointer = ft_nullptr;
    }
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::swap(ft_sharedptr<ManagedType>& other)
{
    std::swap(_managedPointer, other._managedPointer);
    std::swap(_referenceCount, other._referenceCount);
    std::swap(_arraySize, other._arraySize);
    std::swap(_isArrayType, other._isArrayType);
    std::swap(_errorCode, other._errorCode);
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::add(const ManagedType& element)
{
    if (!_isArrayType)
    {
        this->set_error(SHARED_PTR_INVALID_OPERATION);
        return;
    }
    size_t newSize = _arraySize + 1;
    ManagedType* newArray = new (std::nothrow) ManagedType[newSize];
    if (!newArray)
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
        return;
    }
    for (size_t i = 0; i < _arraySize; ++i)
        newArray[i] = _managedPointer[i];
    newArray[_arraySize] = element;
    delete[] _managedPointer;
    _managedPointer = newArray;
    _arraySize = newSize;
}

template <typename ManagedType>
void ft_sharedptr<ManagedType>::remove(int index)
{
    if (!_isArrayType)
    {
        this->set_error(SHARED_PTR_INVALID_OPERATION);
        return;
    }
    if (!_managedPointer || static_cast<size_t>(index) >= _arraySize || index < 0)
    {
        this->set_error(SHARED_PTR_OUT_OF_BOUNDS);
        return;
    }
    size_t newSize = _arraySize - 1;
    ManagedType* newArray = (newSize > 0) ? new (std::nothrow) ManagedType[newSize] : nullptr;
    if (newSize > 0 && !newArray)
    {
        this->set_error(SHARED_PTR_ALLOCATION_FAILED);
        return;
    }
    for (size_t i = 0; i < static_cast<size_t>(index); ++i)
        newArray[i] = _managedPointer[i];
    for (size_t i = index; i < newSize; ++i)
        newArray[i] = _managedPointer[i+1];
    delete[] _managedPointer;
    _managedPointer = newArray;
    _arraySize = newSize;
}

#endif
