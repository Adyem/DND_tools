#include "ostream.hpp"
#include "../CMA/CMA.hpp"
#include "nullptr.hpp"


ft_ostream::ft_ostream()
	: buffer(ft_nullptr), capacity(0), size(0), error_flag(false)
{
	capacity = 64;
	buffer = (char*)cma_malloc((int)capacity, false);
	if (buffer == ft_nullptr) {
		error_flag = true;
		return ;
	}
	buffer[0] = '\0';
	return ;
}

ft_ostream::~ft_ostream()
{
	if (buffer != ft_nullptr)
		cma_free(buffer);
	return ;
}

bool ft_ostream::ensure_capacity(size_t additional_size)
{
    if (error_flag)
        return (false);
    size_t required = size + additional_size + 1;
    if (required <= capacity)
        return (true);
    size_t new_capacity = capacity;
    while (new_capacity < required)
        new_capacity *= 2;
    char* new_buffer = (char*)cma_realloc(buffer, new_capacity, false);
    if (new_buffer == ft_nullptr)
	{
        error_flag = true;
        return (false);
    }
    buffer = new_buffer;
    capacity = new_capacity;
    return (true);
}

ft_ostream& ft_ostream::operator<<(const char* str)
{
    if (error_flag || str == ft_nullptr)
        return (*this);
    size_t len = 0;
    while (str[len])
		len++;
	if (!ensure_capacity(len))
        return (*this);
	size_t i = 0;
    while (i < len) 
	{
        buffer[size + i] = str[i];
		i++;
    }
    size += len;
    buffer[size] = '\0';

    return (*this);
}

ft_ostream& ft_ostream::operator<<(int val)
{
    if (error_flag)
        return (*this);
    char* int_str = cma_itoa(val, false);
    if (int_str == ft_nullptr)
	{
        error_flag = true;
        return (*this);
    }
    size_t len = 0;
    while (int_str[len]) len++;
    if (!ensure_capacity(len)) {
        cma_free(int_str);
        return (*this);
    }
	size_t i = 0;
    while (i < len)
	{
        buffer[size + i] = int_str[i];
		i++;
    }
    size += len;
    buffer[size] = '\0';
    cma_free(int_str);
    return (*this);
}

ft_ostream& ft_ostream::operator<<(char c)
{
    if (error_flag)
        return (*this);
    if (!ensure_capacity(1))
        return (*this);
    buffer[size] = c;
    size += 1;
    buffer[size] = '\0';

    return (*this);
}

int ft_ostream::write(const char* data, size_t len)
{
	if (error_flag || data == ft_nullptr)
		return -1;
	if (len == 0)
		while (data[len]) len++;
	size_t needed = size + len + 1;
	if (needed > capacity) {
		size_t new_capacity = capacity;
		while (new_capacity < needed)
			new_capacity *= 2;
		char* new_buffer = (char*)cma_realloc(buffer, new_capacity, false);
		if (new_buffer == ft_nullptr)
		{
			error_flag = true;
			return (-1);
		}
		buffer = new_buffer;
		capacity = new_capacity;
	}
	size_t i = 0;
	while (i < len)
	{
		buffer[size + i] = data[i];
		i++;
	}
	size += len;
	buffer[size] = '\0';
	return (0);
}

char* ft_ostream::str()
{
	if (error_flag)
		return (char*)ft_nullptr; 
	return (buffer);
}

bool ft_ostream::bad() const
{
	return (error_flag);
}

void ft_ostream::clear()
{
	if (buffer != ft_nullptr)
	{
		cma_free(buffer);
		buffer = ft_nullptr;
	}
	capacity = 64;
	size = 0;
	error_flag = false;
	buffer = (char*)cma_malloc((int)capacity, false);
	if (buffer == ft_nullptr)
	{
		error_flag = true;
		return ;
	}
	buffer[0] = '\0';
	return ;
}
