#include "socket_class.hpp"
#include "../Errno/errno.hpp"
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

ft_socket::ft_socket(const SocketConfig &config) : socket_fd(-1), _error(ER_SUCCESS)
{
    if (config.type == SocketType::SERVER)
        setup_server(config);
    else if (config.type == SocketType::CLIENT)
        setup_client(config);
    else
    {
        ft_errno = SOCKET_UNSUPPORTED_TYPE;
        _error = ft_errno;
    }
	return ;
}

int ft_socket::send_data(const void *data, size_t size, int flags)
{
    if (socket_fd < 0)
	{
        ft_errno = SOCKET_INVALID_CONFIGURATION;
        _error = ft_errno;
        return (-1);
    }
    int bytes_sent = ::send(socket_fd, data, size, flags);
    if (bytes_sent < 0)
	{
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
    }
    else
        _error = ER_SUCCESS;
    return (bytes_sent);
}

int ft_socket::receive_data(void *buffer, size_t size, int flags)
{
    if (socket_fd < 0)
	{
        ft_errno = FT_EINVAL;
        _error = ft_errno;
        return (-1);
	} 
    int bytes_received = ::recv(socket_fd, buffer, size, flags);
    if (bytes_received < 0)
	{
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
    }
    else
        _error = ER_SUCCESS;
    return (bytes_received);
}

bool ft_socket::close_socket()
{
    if (socket_fd >= 0)
	{
        if (::close(socket_fd) == 0)
		{
            socket_fd = -1;
            _error = ER_SUCCESS;
            return (true);
        }
        else
		{
            ft_errno = errno + ERRNO_OFFSET;
            _error = ft_errno;
            return (false);
        }
    }
    _error = ER_SUCCESS;
    return (true);
}

const char* ft_socket::get_error_message() const
{
    return (ft_strerror(_error));
}
