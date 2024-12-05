#ifndef NETWORKING_HPP
# define NETWORKING_HPP

#include "../CPP_class/string.hpp"

enum class SocketType
{
    SERVER,
    CLIENT,
    RAW
};

struct SocketConfig
{
    SocketType type;
	ft_string ip;
    int port;
    int backlog;
};

#endif
