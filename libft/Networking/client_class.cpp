#include "client_class.hpp"
#include "../CPP_class/string.hpp"
#include "../Errno/errno.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <atomic>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <cerrno>

ft_client::ft_client(int client_fd_)
    : _error(0),
      _client_fd(client_fd_),
      closed(false),
      client_addr()
{
    if (this->_client_fd < 0)
    {
        set_error(errno + ERRNO_OFFSET);
        return ;
    }
    retrieve_client_address();
	return ;
}

ft_client::~ft_client()
{
    close_connection();
	return ;
}

ft_client::ft_client(ft_client&& other) noexcept
    : _error(other._error),
      _client_fd(other._client_fd),
      closed(other.closed.load()),
      client_addr(other.client_addr)
{
    other._client_fd = -1;
    other.closed = true;
    other._error = 0;
	return ;
}

ft_client& ft_client::operator=(ft_client&& other) noexcept
{
    if (this != &other)
    {
        close_connection();
        this->_error = other._error;
        this->_client_fd = other._client_fd;
        this->closed = other.closed.load();
        this->client_addr = other.client_addr;
        other._client_fd = -1;
        other.closed = true;
        other._error = 0;
    }
    return (*this);
}

ssize_t ft_client::send_data(const void* data, size_t size, int flags)
{
    if (is_closed())
    {
        set_error((EBADF) + ERRNO_OFFSET);
        return (-1);
    }

    ssize_t bytes_sent = send(this->_client_fd, data, size, flags);
    if (bytes_sent == -1)
        set_error(errno + ERRNO_OFFSET);
    return (bytes_sent);
}

ssize_t ft_client::receive_data(void* buffer, size_t size, int flags)
{
    if (is_closed())
    {
        set_error((EBADF) + ERRNO_OFFSET);
        return (-1);
    }
    ssize_t bytes_received = recv(this->_client_fd, buffer, size, flags);
    if (bytes_received == -1)
        set_error(errno + ERRNO_OFFSET);
    return (bytes_received);
}

void ft_client::close_connection()
{
    bool expected = false;
    if (closed.compare_exchange_strong(expected, true))
    {
        if (this->_client_fd != -1)
        {
            if (close(this->_client_fd) == -1)
                set_error(errno + ERRNO_OFFSET);
            this->_client_fd = -1;
        }
    }
	return ;
}

bool ft_client::is_closed() const
{
    return (closed.load());
}

ft_string ft_client::getClientAddress() const
{
    char host[NI_MAXHOST], service[NI_MAXSERV];
    if (getnameinfo(reinterpret_cast<const struct sockaddr*>(&client_addr),
                    sizeof(client_addr),
                    host, sizeof(host),
                    service, sizeof(service),
                    NI_NUMERICHOST | NI_NUMERICSERV) != 0)
    {
       _error = EFAULT + ERRNO_OFFSET;
	   ft_errno = _error;
        return ("Unknown");
    }
    ft_string address(host);
    address = address + ": " + service;
	if (address.getError())
	{
		this->_error = address.getError();
		ft_errno = this->_error;
	}
    return (address);
}

void ft_client::retrieve_client_address()
{
    socklen_t addr_len = sizeof(client_addr);
	if (getpeername(this->_client_fd, reinterpret_cast<struct sockaddr*>(&client_addr),
			&addr_len) == -1)
		set_error(errno + ERRNO_OFFSET);
	return ;
}

int ft_client::get_fd() const
{
    return (this->_client_fd);
}

void ft_client::set_error(int error)
{
    this->_error = error;
    ft_errno = error;
	return ;
}

const char* ft_client::getErrorMsg(int errorCode) const
{
    return (ft_strerror(errorCode));
}
