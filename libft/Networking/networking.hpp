#ifndef NETWORKING_HPP
#define NETWORKING_HPP

#include "../CPP_class/string.hpp"

enum class SocketType
{
    SERVER,
    CLIENT,
    RAW
};

class SocketConfig
{
	private:
		int _error;

	public:
    	SocketType type;
    	ft_string ip;
    	int port;
    	int backlog;
    	int protocol;
    	int address_family;
    	bool reuse_address;
    	bool non_blocking;
    	int recv_timeout;
    	int send_timeout;
    	ft_string multicast_group;
    	ft_string multicast_interface;

    	SocketConfig();
    	~SocketConfig();

    	SocketConfig(const SocketConfig& other) noexcept;
    	SocketConfig(SocketConfig&& other) noexcept;
    	SocketConfig& operator=(const SocketConfig& other) noexcept;
    	SocketConfig& operator=(SocketConfig&& other) noexcept;

		int getError();
		const char *getStrError();
};

#endif
