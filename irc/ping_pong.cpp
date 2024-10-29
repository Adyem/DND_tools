#include "server_class.hpp"
#include "irc.hpp"
#include <iostream>

void	Server::ft_pong(int fd)
{
	this->getClient(fd)->setTimePong(std::time(NULL));
	return ;
}

int	Server::ft_check_pong(int fd)
{
	if (this->getClient(fd) == NULL)
		return (0);
	if (std::time(NULL) - this->getClient(fd)->getTimePing() > 120)
		return (1);
	return (0);
}

void	Server::ft_send_pong(const std::string &arg, int fd)
{
	std::string message = "PONG :" + arg + "\r\n";
	if (DEBUG == 1)
		std::cout << "sending " << message << std::endl;
	send(fd, message.c_str(), message.size(), 0);
	return ;
}

void Server::ft_sendPing(int fd)
{
	Client *client = this->getClient(fd);

	if (client == NULL)
		return ;
	if (std::time(NULL) - client->getTimePing() < 120)
		return ;
	std::string message = "PING " + client->getNickName() + " \r\n";
	if (DEBUG == 1)
		std::cout << "sending ping " << std::time(NULL) - client->getTimePing() << " " << message << std::endl;
	send(fd, message.c_str(), message.size(), 0);
	this->getClient(fd)->setTimePing(std::time(NULL));
	return ;
}
