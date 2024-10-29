#include "server_class.hpp"
#include "irc.hpp"
#include <iostream>

void	Server::ft_quit(const std::string &arg, int fd)
{
	Client *client = getClient(fd);
	if (!client)
		return ;

	std::string quitMessage = ":" + client->getNickName() + " QUIT :" + (arg.empty() ? "Client quit" : arg) + "\r\n";
	std::vector<Channel>::iterator ic = _channelsList.begin(); 
	while (ic != _channelsList.end())
	{
		if (ic->get_member(fd) || ic->get_admin(fd))
		{
			ic->broadcast(quitMessage, fd);
			ic->removeByNick(client->getNickName());
		}
		ic++;
	}
	for (size_t i = 0; i < _pollfds.size(); ++i)
	{
		if (_pollfds[i].fd == fd)
		{
			_pollfds.erase(_pollfds.begin() + i);
			break ;
		}
	}
	for (size_t i = 0; i < _clientsList.size(); ++i)
	{
		if (_clientsList[i].get_client_FD() == fd)
		{
			_clientsList.erase(_clientsList.begin() + i);
			break ;
		}
	}
	if (DEBUG == 1)
		std::cout << client->getNickName() << " has quit the server." << std::endl;
	close(fd);
	this->_client_number--;
	return ;
}

