#include "networking.hpp"
#include "socket_class.hpp"
#include "../Errno/errno.hpp"
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

int ft_socket::setup_client(const SocketConfig &config)
{
    if (create_socket(config) != ER_SUCCESS)
        return (_error);
    if (config.non_blocking)
        if (set_non_blocking(config) != ER_SUCCESS)
            return (_error);
    if (config.recv_timeout > 0 || config.send_timeout > 0)
        if (set_timeouts(config) != ER_SUCCESS)
            return (_error);
    if (configure_address(config) != ER_SUCCESS)
        return (_error);
    socklen_t addr_len;
    if (config.address_family == AF_INET)
        addr_len = sizeof(struct sockaddr_in);
    else if (config.address_family == AF_INET6)
        addr_len = sizeof(struct sockaddr_in6);
    else
    {
        handle_error(SOCKET_INVALID_CONFIGURATION);
        close(socket_fd);
        socket_fd = -1;
        return (_error);
    }
    if (nw_connect(socket_fd, reinterpret_cast<const struct sockaddr*>(&this->_address),
				addr_len) < 0)
    {
        handle_error(errno + ERRNO_OFFSET);
        close(socket_fd);
        socket_fd = -1;
        return (_error);
    }
    _error = ER_SUCCESS;
    return (_error);
}
