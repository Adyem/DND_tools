#include "channel.hpp"
#include "client_class.hpp"
#include "server_class.hpp"
#include <vector>
#include <cstddef>
#include <sstream>
#include <string>

int Channel::addMember(Client *client)
{
    if (!isMember(client))
	{
        _membersList.push_back(client);
		return (1);
	}
    return (0);
}

void	Server::ft_join(const std::string &arg, int fd)
{
	(void)fd;
	std::stringstream			stringstream(arg);
	std::string					channelName;
	std::vector<std::string>	channelsName;
	size_t						i;

	while (std::getline(stringstream, channelName, ','))
		channelsName.push_back(channelName);
	i = 0;
	while (i < channelsName.size())
	{
		std::string currentChannelName = channelsName[i];
		if (currentChannelName[0] != '&' && currentChannelName[0] != '#')
		{
			std::string errorMessage = "Error - invalid channel name: " + currentChannelName;
			sendResponse(errorMessage, fd);
			i++;
			continue ;
		}
		Channel *channel = getChannelByName(currentChannelName);
		if (!channel)
		{
			std::string errorMessage = "Error - channel doesn't exist: " + currentChannelName;
			sendResponse(errorMessage, fd);
			i++;
			continue ;
		}
		Client *client = getClient(fd);
		if (!client)
		{
			std::string errorMessage = "Error - client doesn't exist: " + currentChannelName;
			sendResponse(errorMessage, fd);
			i++;
			continue ;
		}
		if (channel->addMember(client))
		{
			std::string errorMessage = "Error - " + client->getNickName() +
				" alreaddy member off channel: " + currentChannelName;
			sendResponse(errorMessage, fd);
			i++;
			continue ;
		}
		std::string Message = client->getNickName() + " has joined " + channel->getName();
		channel->broadcast(Message, fd);
		Message = "You have joined the channel " + channel->getName();
		sendResponse(Message, fd);
		i++;
	}
}
