#include "file.hpp"
#include <cerrno>

ft_file::ft_file(const char* filename, int flags, mode_t mode) noexcept 
    : _fd(-1), _error_code(0)
{
    _fd = open(filename, flags, mode);
	if (_fd == -1)
        _error_code = errno;
	return ;
}

ft_file::ft_file(int fd) noexcept 
    : _fd(fd), _error_code(0)
{
	return ;
}

ft_file::~ft_file() noexcept
{
    if (this->_fd >= 0) {
        if (close(this->_fd) == -1)
		{
            if (_error_code == 0)
                _error_code = errno;
        }
    }
	return ;
}

ft_file::ft_file(ft_file&& other) noexcept 
    : _fd(other._fd), _error_code(other._error_code)
{
    other._fd = -1;
    other._error_code = 0;
	return ;
}

ft_file& ft_file::operator=(ft_file&& other) noexcept
{
    if (this != &other)
	{
        if (_fd >= 0)
		{
            if (close(_fd) == -1 && _error_code == 0)
                _error_code = errno;
        }
        _fd = other._fd;
        _error_code = other._error_code;
        other._fd = -1;
        other._error_code = 0;
    }
    return (*this);
}

int ft_file::get_fd() const
{
    return (this->_fd);
}

bool ft_file::has_error() const noexcept
{
    return _error_code != 0;
}

int ft_file::get_error_code() const noexcept
{
    return _error_code;
}

const char *ft_file::get_error_message() const noexcept
{
    if (_error_code != 0) {
        return std::strerror(_error_code);
    }
    return "No error";
}
