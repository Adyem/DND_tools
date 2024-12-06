#include "client_class.hpp"
#include "../CPP_class/string.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <atomic>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <cerrno>

ft_client::ft_client(int client_fd_)
    : client_fd(client_fd_), closed(false), client_addr()
{
    if (client_fd < 0)
    {
        return ;
    }

    retrieve_client_address();
}

ft_client::~ft_client()
{
    close_connection();
}

ft_client::ft_client(ft_client&& other) noexcept
    : client_fd(other.client_fd), closed(other.closed.load()), client_addr(other.client_addr)
{
    other.client_fd = -1;
    other.closed = true;
}

ft_client& ft_client::operator=(ft_client&& other) noexcept
{
    if (this != &other)
    {
        close_connection();

        client_fd = other.client_fd;
        closed = other.closed.load();
        client_addr = other.client_addr;

        other.client_fd = -1;
        other.closed = true;
    }
    return *this;
}

ssize_t ft_client::send_data(const void* data, size_t size, int flags)
{
    if (is_closed())
    {
        return -1;
    }

    ssize_t bytes_sent = send(client_fd, data, size, flags);
    if (bytes_sent == -1)
    {
    }

    return bytes_sent;
}

ssize_t ft_client::receive_data(void* buffer, size_t size, int flags)
{
    if (is_closed())
    {
        return -1;
    }
    ssize_t bytes_received = recv(client_fd, buffer, size, flags);
    if (bytes_received == -1)
    {
    }

    return bytes_received;
}

void ft_client::close_connection()
{
    bool expected = false;
    if (closed.compare_exchange_strong(expected, true))
    {
        if (client_fd != -1)
        {
            if (close(client_fd) == -1)
			{
			}
            client_fd = -1;
        }
    }
}

bool ft_client::is_closed() const
{
    return closed.load();
}

ft_string ft_client::get_client_address() const
{
    char host[NI_MAXHOST], service[NI_MAXSERV];
    if (getnameinfo(reinterpret_cast<const struct sockaddr*>(&client_addr), sizeof(client_addr),
				host, sizeof(host), service, sizeof(service), NI_NUMERICHOST
				| NI_NUMERICSERV) != 0)
    {
        return "Unknown";
    }
    ft_string address = ft_string(host) + ":" + ft_string(service);
    return address;
}

void ft_client::retrieve_client_address()
{
    socklen_t addr_len = sizeof(client_addr);
    if (getpeername(client_fd, reinterpret_cast<struct sockaddr*>(&client_addr), &addr_len) == -1)
	{
	}
}
