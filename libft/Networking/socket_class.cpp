#include "socket_class.hpp"
#include "../Errno/errno.hpp"
#include "../CPP_class/string.hpp"
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
}

int ft_socket::setup_server(const SocketConfig &config)
{
    socket_fd = socket(config.address_family, SOCK_STREAM, config.protocol);
    if (socket_fd < 0)
    {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
        return _error;
    }
    if (config.reuse_address)
    {
        int opt = 1;
        if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        {
            ft_errno = errno + ERRNO_OFFSET;
            _error = ft_errno;
            close(socket_fd);
            socket_fd = -1;
            return _error;
        }
    }
    if (config.non_blocking)
    {
        int flags = fcntl(socket_fd, F_GETFL, 0);
        if (flags == -1)
        {
            ft_errno = errno + ERRNO_OFFSET;
            _error = ft_errno;
            close(socket_fd);
            socket_fd = -1;
            return _error;
        }
        if (fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK) == -1)
        {
            ft_errno = errno + ERRNO_OFFSET;
            _error = ft_errno;
            close(socket_fd);
            socket_fd = -1;
            return _error;
        }
    }
    if (config.recv_timeout > 0)
    {
        struct timeval tv;
        tv.tv_sec = config.recv_timeout / 1000;
        tv.tv_usec = (config.recv_timeout % 1000) * 1000;
        if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
        {
            ft_errno = errno + ERRNO_OFFSET;
            _error = ft_errno;
            close(socket_fd);
            socket_fd = -1;
            return _error;
        }
    }
    if (config.send_timeout > 0)
    {
        struct timeval tv;
        tv.tv_sec = config.send_timeout / 1000;
        tv.tv_usec = (config.send_timeout % 1000) * 1000;
        if (setsockopt(socket_fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0)
        {
            ft_errno = errno + ERRNO_OFFSET;
            _error = ft_errno;
            close(socket_fd);
            socket_fd = -1;
            return _error;
        }
    }
    struct sockaddr_storage addr;
    std::memset(&addr, 0, sizeof(addr));

    if (config.address_family == AF_INET)
    {
        struct sockaddr_in *addr_in = (struct sockaddr_in*)&addr;
        addr_in->sin_family = AF_INET;
        addr_in->sin_port = htons(config.port);
        if (inet_pton(AF_INET, config.ip.c_str(), &addr_in->sin_addr) <= 0)
        {
            ft_errno = SOCKET_INVALID_CONFIGURATION;
            _error = ft_errno;
            close(socket_fd);
            socket_fd = -1;
            return _error;
        }
    }
    else if (config.address_family == AF_INET6)
    {
        struct sockaddr_in6 *addr_in6 = (struct sockaddr_in6*)&addr;
        addr_in6->sin6_family = AF_INET6;
        addr_in6->sin6_port = htons(config.port);
        if (inet_pton(AF_INET6, config.ip.c_str(), &addr_in6->sin6_addr) <= 0)
        {
            ft_errno = SOCKET_INVALID_CONFIGURATION;
            _error = ft_errno;
            close(socket_fd);
            socket_fd = -1;
            return _error;
        }
    }
    else
    {
        ft_errno = SOCKET_INVALID_CONFIGURATION;
        _error = ft_errno;
        close(socket_fd);
        socket_fd = -1;
        return _error;
    }
    if (::bind(socket_fd, (struct sockaddr*)&addr, (config.address_family == AF_INET)
				? sizeof(sockaddr_in) : sizeof(sockaddr_in6)) < 0)
    {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
        close(socket_fd);
        socket_fd = -1;
        return _error;
    }
    if (::listen(socket_fd, config.backlog) < 0)
    {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
        close(socket_fd);
        socket_fd = -1;
        return _error;
    }
    _error = ER_SUCCESS;
    return _error;
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
