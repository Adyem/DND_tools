#include "string.hpp"
#include <cstring>
#include "../CMA/CMA.hpp"
#include "../Libft/libft.hpp"
#include "../Errno/errno.hpp"
#include "nullptr.hpp"

ft_string::ft_string() noexcept 
    : _data(ft_nullptr), _length(0), _capacity(0), _errorCode(0), _criticality(false)
{
    return;
}

ft_string::ft_string(const char* init_str, bool crit) noexcept 
    : _data(ft_nullptr), _length(0), _capacity(0), _errorCode(0), _criticality(crit)
{
    if (init_str)
    {
        this->_length = std::strlen(init_str);
        this->_capacity = this->_length + 1;
        this->_data = static_cast<char*>(cma_malloc(this->_capacity, this->_criticality));
        if (!this->_data)
        {
            this->setError(STRING_MEM_ALLOC_FAIL);
            return;
        }
        ft_memcpy(this->_data, init_str, this->_length + 1);
    }
    return;
}

ft_string::ft_string(const ft_string& other) noexcept 
    : _data(ft_nullptr), _length(other._length), _capacity(other._capacity), 
      _errorCode(other._errorCode), _criticality(other._criticality)
{
    if (other._data)
    {
        this->_data = static_cast<char*>(cma_malloc(this->_capacity, this->_criticality));
        if (!this->_data)
        {
            this->setError(STRING_MEM_ALLOC_FAIL);
            return;
        }
        ft_memcpy(this->_data, other._data, this->_length + 1);
    }
    return;
}

ft_string::ft_string(ft_string&& other) noexcept
    : _data(other._data),
      _length(other._length),
      _capacity(other._capacity),
      _errorCode(other._errorCode),
      _criticality(other._criticality)
{
    other._data = nullptr;
    other._length = 0;
    other._capacity = 0;
    other._errorCode = 0;
    other._criticality = false;
}

ft_string& ft_string::operator=(const ft_string& other) noexcept
{
    if (this == &other)
        return (*this);
    cma_free(this->_data);
    this->_data = ft_nullptr;
    this->_length = other._length;
    this->_capacity = other._capacity;
    this->_errorCode = other._errorCode;
    this->_criticality = other._criticality;
    if (other._data)
    {
        this->_data = static_cast<char*>(cma_malloc(this->_capacity, this->_criticality));
        if (!this->_data)
        {
            this->setError(STRING_MEM_ALLOC_FAIL);
            return (*this);
        }
        ft_memcpy(this->_data, other._data, this->_length + 1);
    }
    return (*this);
}

ft_string& ft_string::operator=(const char*& other) noexcept
{
    cma_free(this->_data);
    this->_data = ft_nullptr;
    this->_length = ft_strlen(other);
    this->_capacity = ft_strlen(other);
    this->_errorCode = 0;
    this->_criticality = false;
    if (other)
    {
        this->_data = static_cast<char*>(cma_malloc(this->_capacity, this->_criticality));
        if (!this->_data)
        {
            this->setError(STRING_MEM_ALLOC_FAIL);
            return (*this);
        }
        ft_memcpy(this->_data, other, this->_length + 1);
    }
    return (*this);
}

ft_string& ft_string::operator=(ft_string&& other) noexcept
{
    if (this != &other)
    {
        delete[] _data;
        _data = other._data;
        _length = other._length;
        _capacity = other._capacity;
        _errorCode = other._errorCode;
        _criticality = other._criticality;
        other._data = nullptr;
        other._length = 0;
        other._capacity = 0;
        other._errorCode = 0;
        other._criticality = false;
    }
    return *this;
}

ft_string::~ft_string()
{
    cma_free(this->_data);
    return;
}