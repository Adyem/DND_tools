#include <iostream>
#include <sys/socket.h>
#include "irc.hpp"
#include "server_class.hpp"

int main(int argc, char **argv)
{
	Server	*info_server;
	int		port;

	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return (1);
	}
	port = ft_check_input(argv[1]);
	if (port == -1)
		return (1);
	try
	{
		info_server = ft_create_socket(port, argv[2]);
	}
	catch(std::exception &e)
	{
		std::cerr << "Runetime error: " << e.what() << std::endl;
	}
	try
	{
		info_server->ft_start_server();
	}
	catch(std::exception &e)
	{
		std::cerr << "Server error: " << e.what() << std::endl;
	}
	delete info_server;
	return (0);
}
