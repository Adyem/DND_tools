#include "server_class.hpp"
#include <sstream>


void	Server::topic(const std::string& arg, int fd)
{
	std::string	prefix = "#&+!";
	std::vector<std::string>	commands = splitString(arg, ' ');

	if ((commands.size() < 1))
	{
		sendResponse(":localhost 461 " + getClient(fd)->getNickName() + " TOPIC :Not enough parameters.\r\n", fd);
		return ;
	}
	if (prefix.find(commands[0][0]) == std::string::npos || !getChannel(commands[0]))
	{
		sendResponse(":localhost 403 " + getClient(fd)->getNickName() + " " + commands[0] + " :No such channel\r\n", fd);
		return ;
	}
	//without extra parameters, TOPIC #channelname would return the topic text, the nickname who set the topic and the time that the topic is set.
	if (commands.size() == 1)
	{
		if (getChannel(commands[0])->getTopic().empty())
		{
			//when the topic is empty
			sendResponse(":localhost 331 " + getClient(fd)->getNickName() + " " + commands[0] + " :No topic is set\r\n", fd);
			return ;
		}
		else
		{
			sendResponse(":localhost 332 " + getClient(fd)->getNickName() + " " + commands[0] + " :" + getChannel(commands[0])->getTopic() + "\r\n", fd);
			sendResponse(":localhost 333 " + getClient(fd)->getNickName() + " " + commands[0] + " " + getChannel(commands[0])->getTopicAuthor() + " " + getChannel(commands[0])->getTopicTime() + "\r\n", fd);
			return ;
		}
	}
	if (!getChannel(commands[0])->get_member(fd) && !getChannel(commands[0])->get_admin(fd))
	{
		sendResponse(":localhost 442 " + getClient(fd)->getNickName() + " " + commands[0] + " :The user is not on this channel.\r\n", fd);
		return ;
	}
	if (getChannel(commands[0])->getTopicLimit() == true && !getChannel(commands[0])->get_admin(fd))
	{
		sendResponse(":localhost 482 " + getClient(fd)->getNickName() + " " + commands[0] + " :You're not channel operator\r\n", fd);
		return ;
	}

	if (commands.size() == 2)
	{
		//" TOPIC #channelname : " would erase the topic
		if (commands[1][0] == ':' && commands[1].size() == 1)
			getChannel(commands[0])->setTopic("");
		else
			getChannel(commands[0])->setTopic(commands[1].substr(1));
		//save who edited the topic and when the topic is edited
		getChannel(commands[0])->setTopicTime();
		getChannel(commands[0])->setTopicAuthor(getClient(fd)->getNickName());
		//return message
		getChannel(commands[0])->broadcast(":" + getClient(fd)->getNickName() + "!" + getClient(fd)->getUserName() + "@" + "localhost TOPIC " + arg + "\r\n", -1);
	}
	else
	{
		//join the words to return the string 
		std::ostringstream oss;
		std::vector<std::string>::iterator i = commands.begin(); 
		i = i + 1;
		while (i != commands.end())
		{
			oss << *i;
			if (i + 1 != commands.end())
				oss << " ";
			i++;
		}
		getChannel(commands[0])->setTopic(oss.str().substr(1));
		getChannel(commands[0])->setTopicTime();
		getChannel(commands[0])->setTopicAuthor(getClient(fd)->getNickName());
		getChannel(commands[0])->broadcast(":" + getClient(fd)->getNickName() + "!" + getClient(fd)->getUserName() + "@" + "localhost TOPIC " + arg + "\r\n", -1);
	}
	return ;
}
