#include "string.hpp"
#include "../CMA/CMA.hpp"
#include "../Libft/libft.hpp"
#include "../Errno/errno.hpp"
#include "nullptr.hpp"

void ft_string::resize(size_t new_capacity) noexcept
{
    if (new_capacity <= this->_capacity)
        return ;
    char* new_data = static_cast<char*>(cma_realloc(this->_data, new_capacity,
				this->_criticality));
    if (!new_data)
    {
        this->setError(STRING_MEM_ALLOC_FAIL);
        return ;
    }
    this->_data = new_data;
    this->_capacity = new_capacity;
    return ;
}

ft_string::ft_string() noexcept 
    : _data(ft_nullptr), _length(0), _capacity(0), _errorCode(0), _criticality(false)
{
    return ;
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
            return ;
        }
        ft_memcpy(this->_data, init_str, this->_length + 1);
    }
    return ;
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
            return ;
        }
        ft_memcpy(this->_data, other._data, this->_length + 1);
    }
    return ;
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

ft_string& ft_string::operator=(const char *&other) noexcept
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

ft_string::~ft_string()
{
    cma_free(this->_data);
    return ;
}

void ft_string::append(char c) noexcept
{
    if (this->_length + 1 >= this->_capacity)
    {
        resize(this->_capacity == 0 ? 16 : this->_capacity * 2);
        if (this->_errorCode)
            return ;
    }
    this->_data[this->_length++] = c;
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
    if (this->_length == 0)
        return (true);
    return (false);
}

int ft_string::getError() const noexcept
{
    return (this->_errorCode);
}

bool ft_string::isCritical() const noexcept
{
    return (this->_criticality);
}

const char *ft_string::errorStr() const noexcept
{
	return (ft_strerror(this->_errorCode));
}

void ft_string::setError(int errorCode) noexcept
{
	this->_errorCode = errorCode;
	ft_errno = errorCode;
	return ;
}
