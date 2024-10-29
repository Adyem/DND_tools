#include "irc.hpp"
#include "server_class.hpp"
#include <stdexcept>

Server	*ft_create_socket(int port, char *password)
{
	Server	*info_server = new Server(port, std::string(password));

	if (info_server->getSocketfd() == -1)
		throw std::runtime_error("Error creating socket");
	return (info_server);
}
