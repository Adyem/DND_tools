#include "socket_class.hpp"
#include "../Errno/errno.hpp"
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <utility>
#include <sys/socket.h>

ft_socket::ft_socket() : _socket_fd(-1), _error(ER_SUCCESS)
{
    std::memset(&_address, 0, sizeof(_address));
}

int ft_socket::send_data(const void *data, size_t size, int flags, int fd)
{
	size_t index = 0;
    while (index < this->_connected.size())
    {
        if (_connected[index].get_fd() == fd)
        {
            int bytes_sent = this->_connected[index].send_data(data, size, flags);
            if (bytes_sent < 0)
			{
				this->_error = errno + ERRNO_OFFSET;
				ft_errno = this->_error;
			}
            return (bytes_sent);
        }
		index++;
    }
    ft_errno = FT_EINVAL;
    this->_error = ft_errno;
    return (-1);
}

int	ft_socket::get_fd() const
{
	return (this->_socket_fd);
}

int ft_socket::broadcast_data(const void *data, size_t size, int flags, int exception)
{
    int total_bytes_sent = 0;
	size_t index = 0;

    while (index < this->_connected.size())
    {
		if (exception == this->_connected[index].get_fd())
		{
			index++;
			continue ;
		}
        int bytes_sent = this->_connected[index].send_data(data, size, flags);
        if (bytes_sent < 0)
		{
			ft_errno = errno + ERRNO_OFFSET;
			_error = ft_errno;
            continue ;
		}
        total_bytes_sent += bytes_sent;
		index++;
    }
    return (total_bytes_sent);
}

int ft_socket::broadcast_data(const void *data, size_t size, int flags)
{
    int total_bytes_sent = 0;
	size_t index = 0;

    while (index < this->_connected.size())
    {
        int bytes_sent = this->_connected[index].send_data(data, size, flags);
        if (bytes_sent < 0)
		{
			ft_errno = errno + ERRNO_OFFSET;
			_error = ft_errno;
            continue ;
		}
        total_bytes_sent += bytes_sent;
		index++;
    }
    return (total_bytes_sent);
}

int ft_socket::accept_connection() 
{
    if (this->_socket_fd < 0)
    {
        ft_errno = FT_EINVAL;
        this->_error = ft_errno;
		return (-1);
    }
    struct sockaddr_storage client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int new_fd = ::accept(this->_socket_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (new_fd < 0)
    {
        ft_errno = errno + ERRNO_OFFSET;
        this->_error = ft_errno;
        return (-1);
    }
    ft_socket new_socket(new_fd, client_addr);
    this->_connected.push_back(std::move(new_socket));
	if (this->_connected.getError())
	{
		ft_errno = VECTOR_ALLOC_FAIL;
		this->_error = ft_errno;
	}
    return (new_fd);
}

ft_socket::ft_socket(int fd, const sockaddr_storage &addr) : _address(addr), _socket_fd(fd),
						_error(ER_SUCCESS)
{
	return ;
}

ft_socket::ft_socket(const SocketConfig &config) : _socket_fd(-1), _error(ER_SUCCESS)
{
    if (config.type == SocketType::SERVER)
        setup_server(config);
    else if (config.type == SocketType::CLIENT)
        setup_client(config);
    else
    {
        ft_errno = SOCKET_UNSUPPORTED_TYPE;
        this->_error = ft_errno;
    }
	return ;
}

ft_socket::~ft_socket()
{
	close(this->_socket_fd);
	return ;
}

int ft_socket::send_data(const void *data, size_t size, int flags)
{
    if (this->_socket_fd < 0)
	{
        ft_errno = SOCKET_INVALID_CONFIGURATION;
        this->_error = ft_errno;
        return (-1);
    }
    int bytes_sent = ::send(this->_socket_fd, data, size, flags);
    if (bytes_sent < 0)
	{
        ft_errno = errno + ERRNO_OFFSET;
        this->_error = ft_errno;
    }
    else
        this->_error = ER_SUCCESS;
    return (bytes_sent);
}

int ft_socket::receive_data(void *buffer, size_t size, int flags)
{
    if (this->_socket_fd < 0)
	{
        ft_errno = FT_EINVAL;
        this->_error = ft_errno;
        return (-1);
	} 
    int bytes_received = ::recv(this->_socket_fd, buffer, size, flags);
    if (bytes_received < 0)
	{
        ft_errno = errno + ERRNO_OFFSET;
        this->_error = ft_errno;
    }
    else
        this->_error = ER_SUCCESS;
    return (bytes_received);
}

bool ft_socket::close_socket()
{
    if (this->_socket_fd >= 0)
	{
        if (::close(this->_socket_fd) == 0)
		{
            this->_socket_fd = -1;
            this->_error = ER_SUCCESS;
            return (true);
        }
        else
		{
            ft_errno = errno + ERRNO_OFFSET;
            this->_error = ft_errno;
            return (false);
        }
    }
    this->_error = ER_SUCCESS;
    return (true);
}

const char* ft_socket::get_error_message() const
{
    return (ft_strerror(this->_error));
}

ft_socket::ft_socket(ft_socket &&other) noexcept
    : _address(other._address), _socket_fd(other._socket_fd), _error(other._error),
		_connected(std::move(other._connected))
{
    other._socket_fd = -1;
}

ft_socket &ft_socket::operator=(ft_socket &&other) noexcept
{
    if (this != &other)
	{
        close_socket();
        this->_address = other._address;
        this->_socket_fd = other._socket_fd;
        this->_error = other._error;
        this->_connected = std::move(other._connected);
        other._socket_fd = -1;
    }
    return *this;
}
