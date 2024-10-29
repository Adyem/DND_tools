#include "server_class.hpp"
#include <string>
#include <iostream>

char	*ft_strchr(const char *s, int i)
{
	char	c;

	if (!s)
		return (NULL);
	c = (char)i;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

//compare the password from client and the server
void	Server::check_pw(const std::string &arg, int fd)
{
	Client *cli = getClient(fd);

	if (!cli)
	{
		std::cerr << "Error obtaining client record." << std::endl;
	}
	if (cli->getNickName().empty())
		cli->setNickName("*");
	//split the arg into multiple parameters and check if the number of parameters correct.
	std::vector<std::string> commands = splitString(arg, ' ');
	if (commands.size() < 1)
		sendResponse(":localhost 461 " + cli->getNickName() + " PASS :Not enough parameters.\r\n", fd);
	else if (!cli->getRegistered())
	{
		std::string pass = commands[0];
		if (pass == _password)
			cli->setRegistered(true);
		else
			sendResponse(":localhost 464 " + cli->getNickName() + " :Password incorrect.\r\n", fd);
	}
	else
		sendResponse(":localhost 462 " + cli->getNickName() + " :You may not reregister.\r\n", fd);
}

//save the username from client
void	Server::set_username(const std::string& arg, int fd)
{
	//split the arg into multiple parameters and get the client object
	std::vector<std::string> commands = splitString(arg, ' ');
	Client *cli = getClient(fd);

	//check if the client has typed the correct password before.
	if (!cli || !cli->getRegistered())
	{
		sendResponse("You have not registered correctly.\r\n", fd);
		return ;
	}
	if (cli->getNickName().empty())
		cli->setNickName("*");
	//check if the number of parameters correct.
	if ((cli && commands.size() < 4))
	{
		sendResponse(":localhost 461 " + cli->getNickName() + " USER :Not enough parameters.\r\n", fd);
		return;
	}
	//check if the username is already set before.
	else if (cli && !cli->getUserName().empty())
		sendResponse(":localhost 462 " + cli->getNickName() + " :You may not reregister.\r\n", fd);
	else
		cli->setUserName(commands[0]);
	//if the client hasn't logged in, log them in.
	if (!cli->getNickName().empty() && cli->getNickName() != "*"  && !cli->getLoggedIn())
	{
		cli->setLoggedin(true);
		sendResponse(":localhost 001 " + cli->getNickName() + " :Welcome to the IRC server!\r\n", fd);
	}
}

//check if the nickname is used by other people
bool	Server::nicknameInUse(const std::string& nickname)
{
	size_t	i;

	i = 0;
	while (i < this->_clientsList.size())
	{
		if (this->_clientsList[i].getNickName() == nickname)
			return (true);
		i++;
	}
	return (false);
}

//check if the nickname contains invalid characters
bool	Server::is_validNickname(std::string& nickname)
{
	if (nickname.empty())
		return (false);
	for (size_t i = 0; i < nickname.size(); i++)
	{
		if(!std::isalnum(nickname[i]) && !ft_strchr("`|^_-{}[]\\", nickname[i]))
			return (false);
	}
	return (true);
}


void	Server::broadcastNickChange(const std::string& oldNick, const std::string& newNick)
{
	std::vector<Channel>::iterator i = _channelsList.begin();
	while (i != _channelsList.end())
	{
		if (i->getMemberByNick(newNick) || i->getAdminByNick(newNick) )
			i->broadcast(":" + oldNick + "!" + i->getMemberByNick(newNick)->getUserName() + "@localhost NICK :" + newNick + "\r\n", 0);
		i++;
	}
	return ;
}

//save nickname from client
void	Server::set_nickname(const std::string& arg, int fd)
{
	//split the arg into multiple parameters and get the client object
	std::vector<std::string> commands = splitString(arg, ' ');
	Client *cli = getClient(fd);

	//check if the client has typed the correct password before.
	if (!cli || !cli->getRegistered())
	{
		sendResponse("You have not registered correctly.\r\n", fd);
		return ;
	}
	if (cli->getNickName().empty())
		cli->setNickName("*");
	//check if the number of parameters correct.
	if (cli && (commands.size() < 1 || commands[0].empty()))
	{
		sendResponse(":localhost 431 " + cli->getNickName() + " :There is no nickname.\r\n", fd);
		return;
	}
	//check if the nickname is used by someone else.
	if (nicknameInUse(commands[0]) && cli->getNickName() != commands[0])
	{
		sendResponse(":localhost 433 " + cli->getNickName() + " " + commands[0] + " :Nickname is already in use.\r\n", fd);
		return;
	}
	//check if the nickname valid.
	if (!is_validNickname(commands[0]))
	{
		sendResponse(":localhost 432 " + cli->getNickName() + " " + commands[0] + " :Erroneus nickname\r\n", fd);
		return;
	}
	//save the old nickname of existing user before replacement
	std::string oldname = cli->getNickName();
	cli->setNickName(commands[0]);
	//in case of existing clients, send message regarding successful operation.
	if (!oldname.empty() && oldname != commands[0])
	{
		if (oldname == "*")
			sendResponse(commands[0] + ": Nickname changed to " + commands[0] + ".\r\n", fd);
		else
		{
			sendResponse(oldname + ": Nickname changed to " + commands[0] + ".\r\n", fd);
			broadcastNickChange(oldname, commands[0]);
		}
	}
	//if the client hasn't logged in, log them in.
	if (!cli->getUserName().empty() && !cli->getNickName().empty() && cli->getNickName() != "*" && !cli->getLoggedIn())
	{
		cli->setLoggedin(true);
		sendResponse(":localhost 001 " + cli->getNickName() + " :Welcome to the IRC server!\r\n", fd);
	}
	return ;
}