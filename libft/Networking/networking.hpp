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
    SocketType type;          // TCP, UDP, etc.
    ft_string ip;             // IP address to bind/connect to
    int port;                 // Port number
    int backlog;              // Maximum connection queue length (server)
    int protocol;             // Protocol (e.g., IPPROTO_TCP, IPPROTO_UDP)
    int address_family;       // AF_INET (IPv4) or AF_INET6 (IPv6)
    bool reuse_address;       // Allow address reuse
    bool non_blocking;        // Non-blocking mode
    int recv_timeout;         // Receive timeout (ms)
    int send_timeout;         // Send timeout (ms)
    ft_string multicast_group; // Multicast group address (optional)
    ft_string multicast_interface; // Multicast interface (optional)
};

#endif
