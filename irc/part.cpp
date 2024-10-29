#include "server_class.hpp"
#include <sstream>

void	Server::part(const std::string& arg, int fd)
{
	std::string	prefix = "#&+!";
	std::vector<std::string>	commands = splitString(arg, ' ');

	if ((commands.size() < 1))
	{
		sendResponse(":localhost 461 " + getClient(fd)->getNickName() + " PART :Not enough parameters.\r\n", fd);
		return ;
	}
	if (prefix.find(commands[0][0]) == std::string::npos || !getChannel(commands[0]))
	{
		sendResponse(":localhost 403 " + getClient(fd)->getNickName() + " " + commands[0] + " :No such channel\r\n", fd);
		return ;
	}
	if (!getChannel(commands[0])->get_member(fd) && !getChannel(commands[0])->get_admin(fd))
	{
		sendResponse(":localhost 442 " + getClient(fd)->getNickName() + " " + commands[0] + " :The user is not on this channel.\r\n", fd);
		return ;
	}
	if (commands.size() == 1)
	{
		getChannel(commands[0])->broadcast(":" + getClient(fd)->getNickName() + "!" + getClient(fd)->getUserName() + "@" + "localhost PART " + commands[0] + "\r\n", 0);
		getChannel(commands[0])->removeByNick(getClient(fd)->getNickName());
	}
	else
	{
		std::ostringstream oss;
		std::vector<std::string>::iterator i = commands.begin(); 
		i = i + 1;
		oss << " :";
		while (i != commands.end())
		{
			oss << *i << " ";
			i++;
		}
		getChannel(commands[0])->broadcast(":" + getClient(fd)->getNickName() + "!" + getClient(fd)->getUserName() + "@" + "localhost PART " + commands[0] + oss.str() + "\r\n", 0);
		getChannel(commands[0])->removeByNick(getClient(fd)->getNickName());
	}
	return ;
}
