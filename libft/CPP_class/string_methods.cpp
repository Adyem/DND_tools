#include "string.hpp"
#include <cstring>
#include "../CMA/CMA.hpp"
#include "../Errno/errno.hpp"
#include "nullptr.hpp"

void ft_string::resize(size_t new_capacity) noexcept
{
    if (new_capacity <= this->_capacity)
        return;
    char* new_data = static_cast<char*>(cma_realloc(this->_data, new_capacity,
                this->_criticality));
    if (!new_data)
    {
        this->setError(STRING_MEM_ALLOC_FAIL);
        return;
    }
    this->_data = new_data;
    this->_capacity = new_capacity;
    return;
}

void ft_string::append(char c) noexcept
{
    if (this->_length + 1 >= this->_capacity)
    {
        resize(this->_capacity == 0 ? 16 : this->_capacity * 2);
        if (this->_errorCode)
            return;
    }
    this->_data[this->_length++] = c;
    this->_data[this->_length] = '\0';
    return;
}

void ft_string::clear() noexcept
{
    this->_length = 0;
    if (this->_data)
        this->_data[0] = '\0';
    this->_errorCode = 0;
    return;
}

const char* ft_string::at(size_t index) const noexcept
{
    if (index >= this->_length)
        return (ft_nullptr);
    return (&this->_data[index]);
}

const char* ft_string::c_str() const noexcept
{
    if (this->_data)
        return (this->_data);
    return (const_cast<char *>(""));
}

char* ft_string::print() noexcept
{
    if (this->_data)
        return (this->_data);
    return (const_cast<char *>(""));
}

size_t ft_string::size() const noexcept
{
    return (this->_length);
}

bool ft_string::empty() const noexcept
{
    return (this->_length == 0);
}

int ft_string::getError() const noexcept
{
    return (this->_errorCode);
}

bool ft_string::isCritical() const noexcept
{
    return (this->_criticality);
}

const char* ft_string::errorStr() const noexcept
{
    return (ft_strerror(this->_errorCode));
}

void ft_string::setError(int errorCode) noexcept
{
    this->_errorCode = errorCode;
    ft_errno = errorCode;
    return ;
}

void ft_string::move(ft_string& other) noexcept
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
	return ;
}