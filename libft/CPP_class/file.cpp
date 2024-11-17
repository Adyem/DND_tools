#include "file.hpp"

ft_file::ft_file(const char* filename, int flags, mode_t mode) noexcept : _fd(-1)
{
    _fd = open(filename, flags, mode);
	return ;
}

ft_file::ft_file(int fd) noexcept : _fd(fd) 
{
	return ;
}

ft_file::~ft_file() noexcept
{
	if (this->_fd >= 0)
        close(this->_fd);
	return ;
}

int ft_file::get_fd() const
{
    return (this->_fd);
}
