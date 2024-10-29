#include "server_class.hpp"
#include "irc.hpp"
#include <iostream>

void	Server::cap(const std::string &arg, int fd)
{
	if (arg == "LS")
	{
		std::string message = ":localhost CAP * LS :\r\n";
		if (DEBUG == 1)
			std::cout << "responding CAP" << message << std::endl;
		send(fd, message.c_str(), message.size(), 0);
	}
	else if (arg == "REQ")
	{
		std::string message = ":localhost CAP * NAK :unsupported-feature\r\n";
		if (DEBUG == 1)
			std::cout << "sending CAP NAK" << message << std::endl;
		send(fd, message.c_str(), message.size(), 0);
	}
	else if (arg == "END")
		return;
	else
	{
		std::string message = ":localhost 410 * CAP :Invalid CAP subcommand\r\n";
		if (DEBUG == 1)
			std::cout << "responding invalid CAP" << message << std::endl;
		send(fd, message.c_str(), message.size(), 0);
	}
	return ;
}
