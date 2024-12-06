#include "networking.hpp"
#include "../Errno/errno.hpp"
#include <cstring>
#include <sys/socket.h>

SocketConfig::SocketConfig()
    : type(SocketType::SERVER),
      ip("0.0.0.0"),
      port(0),
      backlog(10),
      protocol(0),
      address_family(AF_INET),
      reuse_address(false),
      non_blocking(false),
      recv_timeout(0),
      send_timeout(0),
      multicast_group(""),
      multicast_interface("")
{
	if (ip.getError())
	{
		_error = ip.getError();
		return ;
	}
	if (multicast_group.getError())
	{
		_error = multicast_group.getError();
		return ;
	}
	if (multicast_interface.getError())
	{
		_error = multicast_interface.getError();
		return ;
	}
	return ;
}

SocketConfig::SocketConfig(SocketType type, const ft_string& ip, int port, int backlog,
                int protocol, int address_family, bool reuse_address, bool non_blocking,
				int recv_timeout, int send_timeout, const ft_string& multicast_group,
                const ft_string& multicast_interface)
    : type(type),
      ip(ip),
      port(port),
      backlog(backlog),
      protocol(protocol),
      address_family(address_family),
      reuse_address(reuse_address),
      non_blocking(non_blocking),
      recv_timeout(recv_timeout),
      send_timeout(send_timeout),
      multicast_group(multicast_group),
      multicast_interface(multicast_interface)
{
	return ;
}

SocketConfig::~SocketConfig()
{
	return ;
}

int SocketConfig::getError()
{
	return (_error);
}

const char *SocketConfig::getStrError()
{
	return (ft_strerror(_error));
}
