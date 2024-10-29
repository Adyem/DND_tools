#include "server_class.hpp"
#include <sstream>


void	Server::kick(const std::string& arg, int fd)
{
	std::string	prefix = "#&+!";
	std::vector<std::string>	commands = splitString(arg, ' ');

	if ((commands.size() < 2))
	{
		sendResponse(":localhost 461 " + getClient(fd)->getNickName() + " KICK :Not enough parameters.\r\n", fd);
		return ;
	}
	if (prefix.find(commands[0][0]) == std::string::npos || !getChannel(commands[0]))
	{
		sendResponse(":localhost 403 " + getClient(fd)->getNickName() + " " + commands[0] + " :No such channel\r\n", fd);
		return ;
	}
	if (!getClientByNickname(commands[1]))
	{
		sendResponse(":localhost 401 " + getClient(fd)->getNickName() + " " + commands[1] + " :No such nick/channel\r\n", fd);
		return ;
	}
	if (!getChannel(commands[0])->get_admin(fd))
	{
		sendResponse(":localhost 482 " + getClient(fd)->getNickName() + " " + commands[0] + " :You're not channel operator\r\n", fd);
		return ;
	}
	if (commands[0] == getChannel(commands[0])->get_admin(fd)->getNickName())
	{
		sendResponse(":localhost 482 " + getClient(fd)->getNickName() + " " + commands[0] + " :You cannot kick yourself\r\n", fd);
		return ;
	}
	if (!getChannel(commands[0])->getMemberByNick(commands[1]) && !getChannel(commands[0])->getAdminByNick(commands[1]))
	{
		sendResponse(":localhost 441 " + getClient(fd)->getNickName() + " " + commands[1] + " " + commands[0] + " :They aren't on that channel\r\n", fd);
		return ;
	}
	if (commands.size() == 2)
	{
		getChannel(commands[0])->broadcast(":" + getClient(fd)->getNickName() + "!" + getClient(fd)->getUserName() + "@" + "localhost KICK " + commands[0] + " " + commands[1] + "\r\n", 0);
		getChannel(commands[0])->removeByNick(commands[1]);
	}
	else
	{
		std::ostringstream oss;
		std::vector<std::string>::iterator i = commands.begin(); 
		i = i + 2;
		oss << " :";
		while (i != commands.end())
		{
			oss << *i << " ";
			i++;
		}
		getChannel(commands[0])->broadcast(":" + getClient(fd)->getNickName() + "!" + getClient(fd)->getUserName() + "@" + "localhost KICK " + commands[0] + " " + commands[1] + oss.str() + "\r\n", 0);
		getChannel(commands[0])->removeByNick(commands[1]);
	}
	return ;
}
