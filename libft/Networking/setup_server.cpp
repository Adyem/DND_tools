#include "networking.hpp"
#include "socket_class.hpp"
#include "../Errno/errno.hpp"
#include "../CPP_class/string.hpp"
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

int ft_socket::create_socket(const SocketConfig &config)
{
    this->_socket_fd = nw_socket(config.address_family, SOCK_STREAM, config.protocol);
    if (this->_socket_fd < 0)
	{
        handle_error(errno + ERRNO_OFFSET);
        return (this->_error);
    }
    return (ER_SUCCESS);
}

int ft_socket::set_reuse_address(const SocketConfig &config)
{
    if (!config.reuse_address)
        return (ER_SUCCESS);
    int opt = 1;
    if (setsockopt(this->_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
        handle_error(errno + ERRNO_OFFSET);
        close(this->_socket_fd);
        this->_socket_fd = -1;
        return (this->_error);
    }
    return (ER_SUCCESS);
}

int ft_socket::set_non_blocking(const SocketConfig &config)
{
    if (!config.non_blocking)
        return (ER_SUCCESS);
    int flags = fcntl(this->_socket_fd, F_GETFL, 0);
    if (flags == -1)
	{
        handle_error(errno + ERRNO_OFFSET);
        close(this->_socket_fd);
        this->_socket_fd = -1;
        return (this->_error);
    }

    if (fcntl(this->_socket_fd, F_SETFL, flags | O_NONBLOCK) == -1)
	{
        handle_error(errno + ERRNO_OFFSET);
        close(this->_socket_fd);
        this->_socket_fd = -1;
        return (this->_error);
    }

    return (ER_SUCCESS);
}

int ft_socket::set_timeouts(const SocketConfig &config)
{
    struct timeval tv;
    if (config.recv_timeout > 0)
	{
        tv.tv_sec = config.recv_timeout / 1000;
        tv.tv_usec = (config.recv_timeout % 1000) * 1000;
        if (setsockopt(this->_socket_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
		{
            handle_error(errno + ERRNO_OFFSET);
            close(this->_socket_fd);
            this->_socket_fd = -1;
            return (this->_error);
        }
    }
    if (config.send_timeout > 0)
	{
        tv.tv_sec = config.send_timeout / 1000;
        tv.tv_usec = (config.send_timeout % 1000) * 1000;
        if (setsockopt(this->_socket_fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0)
		{
            handle_error(errno + ERRNO_OFFSET);
            close(this->_socket_fd);
            this->_socket_fd = -1;
            return (this->_error);
        }
    }
    return (ER_SUCCESS);
}

int ft_socket::configure_address(const SocketConfig &config)
{
    std::memset(&this->_address, 0, sizeof(this->_address));

    if (config.address_family == AF_INET)
	{
        struct sockaddr_in *addr_in = reinterpret_cast<struct sockaddr_in*>(&this->_address);
        addr_in->sin_family = AF_INET;
        addr_in->sin_port = htons(config.port);
        if (inet_pton(AF_INET, config.ip.c_str(), &addr_in->sin_addr) <= 0)
		{
            handle_error(SOCKET_INVALID_CONFIGURATION);
            close(this->_socket_fd);
            this->_socket_fd = -1;
            return (this->_error);
        }
    }
    else if (config.address_family == AF_INET6)
	{
        struct sockaddr_in6 *addr_in6 = reinterpret_cast<struct sockaddr_in6*>(&this->_address);
        addr_in6->sin6_family = AF_INET6;
        addr_in6->sin6_port = htons(config.port);
        if (inet_pton(AF_INET6, config.ip.c_str(), &addr_in6->sin6_addr) <= 0)
		{
            handle_error(SOCKET_INVALID_CONFIGURATION);
            close(this->_socket_fd);
            this->_socket_fd = -1;
            return (_error);
        }
    }
    else
	{
        handle_error(SOCKET_INVALID_CONFIGURATION);
        close(this->_socket_fd);
        this->_socket_fd = -1;
        return (this->_error);
    }
    return (ER_SUCCESS);
}

int ft_socket::bind_socket(const SocketConfig &config)
{
    socklen_t addr_len;

    if (config.address_family == AF_INET)
        addr_len = sizeof(struct sockaddr_in);
    else if (config.address_family == AF_INET6)
        addr_len = sizeof(struct sockaddr_in6);
    else
    {
        handle_error(SOCKET_INVALID_CONFIGURATION);
        close(this->_socket_fd);
        this->_socket_fd = -1;
        return (this->_error);
    }
    if (nw_bind(this->_socket_fd, reinterpret_cast<const struct sockaddr*>(&this->_address), addr_len) < 0)
    {
        handle_error(errno + ERRNO_OFFSET);
        close(this->_socket_fd);
        this->_socket_fd = -1;
        return (this->_error);
    }
    return (ER_SUCCESS);
}


int ft_socket::listen_socket(const SocketConfig &config)
{
    if (nw_listen(this->_socket_fd, config.backlog) < 0)
	{
        handle_error(errno + ERRNO_OFFSET);
        close(this->_socket_fd);
        this->_socket_fd = -1;
        return (this->_error);
    }
    return (ER_SUCCESS);
}

void ft_socket::handle_error(int error_code)
{
    ft_errno = error_code;
    this->_error = ft_errno;
	return ;
}

int ft_socket::setup_server(const SocketConfig &config)
{
    if (create_socket(config) != ER_SUCCESS)
        return (this->_error);
    if (config.reuse_address)
        if (set_reuse_address(config) != ER_SUCCESS)
            return (this->_error);
    if (config.non_blocking)
        if (set_non_blocking(config) != ER_SUCCESS)
            return (this->_error);
    if (config.recv_timeout > 0 || config.send_timeout > 0)
        if (set_timeouts(config) != ER_SUCCESS)
            return (this->_error);
    if (configure_address(config) != ER_SUCCESS)
        return (this->_error);
    if (bind_socket(config) != ER_SUCCESS)
        return (this->_error);
    if (listen_socket(config) != ER_SUCCESS)
        return (this->_error);
    this->_error = ER_SUCCESS;
    return (this->_error);
}
