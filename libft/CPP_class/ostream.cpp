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

ft_ostream& ft_ostream::operator<<(const char* str)
{
	if (error_flag || str == ft_nullptr)
		return (*this);
	size_t len = 0;
	while (str[len])
		len++;
	write(str, len);
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
		return *this;
	}
	write(int_str, 0);
	cma_free(int_str);
	return *this;
}

ft_ostream& ft_ostream::operator<<(char c)
{
	if (error_flag)
		return (*this);
	char temp[2];
	temp[0] = c;
	temp[1] = '\0';
	write(temp, 1); 
	return *this;
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
