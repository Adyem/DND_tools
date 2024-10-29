#include "channel.hpp"
#include "client_class.hpp"
#include "server_class.hpp"
#include "irc.hpp"
#include <iostream>

void	Server::ft_notice(const std::string &arg, int fd)
{
	size_t colonPos = arg.find(':');

	if (colonPos == std::string::npos)
	{

		std::string errorMessage = "Invalid Notice format: " + arg;
		this->sendResponse(errorMessage, fd);
		return ;
	}
	std::string target = arg.substr(0, colonPos);
	target.erase(target.find_last_not_of(" \t") + 1);
	std::string message = arg.substr(colonPos + 1);
	if (DEBUG == 1)
	{
		std::cout << "Target: " << target << std::endl;
		std::cout << "Message: " << message << std::endl;
	}
	if (target[0] == '&' || target[0] == '#')
	{
		Channel *channel = this->getChannel(target);
		if (!channel)
		{
			std::string errorMessage = "Channel does not exist: " + target;
			this->sendResponse(errorMessage, fd);
			return ;
		}
		channel->broadcast(message, -1);
	}
	else
	{
		Client *client = this->getClientByNickname(target);
		if (!client)
		{
			std::string errorMessage = "User does not exist: " + target;
			this->sendResponse(errorMessage, fd);
			return ;
		}
		sendResponse(message, client->get_client_FD());
	}
	return ;
}
