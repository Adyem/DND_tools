#include "string.hpp"
#include <cstring>
#include "../CMA/CMA.hpp"
#include "../Libft/libft.hpp"
#include "../Errno/errno.hpp"
#include "nullptr.hpp"

void ft_string::resize(size_t new_capacity) noexcept
{
    if (new_capacity <= this->_capacity)
        return ;
    char* new_data = static_cast<char*>(cma_realloc(this->_data, new_capacity));
    if (!new_data)
    {
        this->setError(STRING_MEM_ALLOC_FAIL);
        return ;
    }
    this->_data = new_data;
    this->_capacity = new_capacity;
    return ;
}

void ft_string::append(char c) noexcept
{
    if (this->_length + 1 >= this->_capacity)
    {
        size_t new_capacity = this->_capacity;
        if (new_capacity == 0)
            new_capacity = 16;
        else
            new_capacity *= 2;
        resize(new_capacity);
        if (this->_errorCode)
            return ;
    }
    this->_data[this->_length++] = c;
    this->_data[this->_length] = '\0';
    return ;
}

void ft_string::append(const ft_string& string) noexcept
{
    if (string._length == 0)
        return ;
    size_t new_length = this->_length + string._length;
    if (new_length >= this->_capacity)
    {
        size_t new_capacity = this->_capacity;
        if (new_capacity == 0)
            new_capacity = 16;
        while (new_capacity <= new_length)
            new_capacity *= 2;
        resize(new_capacity);
        if (this->_errorCode)
            return ;
    }
    std::memcpy(this->_data + this->_length, string._data, string._length);
    this->_length = new_length;
    this->_data[this->_length] = '\0';
	return ;
}

void ft_string::append(const char *string) noexcept
{
    if (!string)
        return ;
    size_t string_length = std::strlen(string);
    if (this->_length + string_length >= this->_capacity)
    {
        size_t new_capacity;
        if (this->_capacity == 0)
            new_capacity = 16;
        else
            new_capacity = this->_capacity;
        while (this->_length + string_length >= new_capacity)
            new_capacity *= 2;
        resize(new_capacity);
        if (this->_errorCode)
            return ;
    }
    std::memcpy(this->_data + this->_length, string, string_length);
    this->_length += string_length;
    this->_data[this->_length] = '\0';
    return ;
}

void ft_string::clear() noexcept
{
    this->_length = 0;
    if (this->_data)
        this->_data[0] = '\0';
    this->_errorCode = 0;
    return ;
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
        cma_free(_data);
        _data = other._data;
        _length = other._length;
        _capacity = other._capacity;
        _errorCode = other._errorCode;
        other._data = nullptr;
        other._length = 0;
        other._capacity = 0;
        other._errorCode = 0;
    }
	return ;
}

ft_string& ft_string::operator+=(const ft_string& other) noexcept
{
	size_t index = 0;

    while (index < other._length)
	{
        this->append(other._data[index]);
		if (_errorCode)
			return (*this);
		index++;
	}
    return (*this);
}

ft_string& ft_string::operator+=(const char* cstr) noexcept
{
    if (cstr)
	{
        size_t i = 0;
        while (cstr[i] != '\0')
		{
            this->append(cstr[i]);
			if (_errorCode)
				return (*this);
            ++i;
        }
    }
    return (*this);
}

ft_string& ft_string::operator+=(char c) noexcept
{
    this->append(c);
    return (*this);
}

void ft_string::erase(size_t index, int count) noexcept
{
    if (index >= this->_length || count < 0)
    {
        this->setError(STRING_ERASE_OUT_OF_BOUNDS);
        return ;
    }
    if (index + count > this->_length)
        count = this->_length - index;
    if (count > 0)
    {
        ft_memmove(this->_data + index, this->_data + index + count,
				this->_length - index - count);
        this->_length -= count;
        this->_data[this->_length] = '\0';
    }
    return ;
}

ft_string operator+(const ft_string &lhs, const ft_string &rhs) noexcept
{
    ft_string result(lhs);
    result += rhs;
    return (result);
}

ft_string operator+(const ft_string &lhs, const char *rhs) noexcept
{
    ft_string result(lhs);
    result += rhs;
    return (result);
}

ft_string operator+(const char *lhs, const ft_string &rhs) noexcept
{
    ft_string result;
    if (lhs)
        result = lhs;
    else
        result = "";
    result += rhs;
    return (result);
}

ft_string operator+(const ft_string &lhs, char rhs) noexcept
{
    ft_string result(lhs);
    result += rhs;
    return (result);
}

ft_string operator+(char lhs, const ft_string &rhs) noexcept
{
    ft_string result;
    result += lhs;
    result += rhs;
    return (result);
}

bool operator==(const ft_string &lhs, const ft_string &rhs) noexcept
{
    return (ft_strcmp(lhs.c_str(), rhs.c_str()) == 0);
}

bool operator==(const ft_string &lhs, const char* rhs) noexcept
{
    return (ft_strcmp(lhs.c_str(), rhs) == 0);
}

bool operator==(const char* lhs, const ft_string &rhs) noexcept
{
    return (ft_strcmp(lhs, rhs.c_str()) == 0);
}
