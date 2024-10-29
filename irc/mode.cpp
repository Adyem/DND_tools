#include "server_class.hpp"
#include <sstream>
#include <map>
#include <string>
#include "irc.hpp"

int	ft_strtoi(std::string str)
{
	int	stri;
	int	ret;
	int	negative;

	stri = 0;
	ret = 0;
	negative = 0;
	while ((str[stri] >= 9 && str[stri] <= 13) || str[stri] == 32)
		stri++;
	if (str[stri] == '-')
	{
		negative = 1;
		stri++;
	}
	else if (str[stri] == '+')
		stri++;
	while (str[stri] >= 48 && str[stri] <= 57)
	{
		ret *= 10;
		ret = ret + str[stri++] - 48;
	}
	if (negative == 1)
		return (-ret);
	else
		return (ret);
}

int	countFlags(std::string str, std::string nick, int fd)
{
	size_t		i;
	int			ret;
	int			haswithout;
	std::string	with = "klo";
	std::string	without = "it";
	char		sign;

	if (str[0] != '+' && str[0] != '-')
		return (-1);
	i = 0;
	ret = 0;
	haswithout = 0;
	sign = str[0];
	while (i < str.size())
	{
		if (str[i] == '+' || str[i] == '-')
		{
			sign = str[i];
			if ((i + 1) >= str.size())
				return (-1);
			if (with.find(str[i + 1]) != std::string::npos && !(str[i] == '-' && str[i + 1] == 'l'))
			{
				if (haswithout == 1) // flags without extra parameter cannot be before flags with extra parameter, otherwise there would be an alignment issue.
					return (-1);
				ret++;
				i++;
			}
			else if (without.find(str[i + 1]) == std::string::npos && str[i + 1] != 'l')
			{
				// check if it is a supported flag
				Server::sendResponse(":localhost 472 " + nick + " " + str[i + 1] + " :is unknown mode char to me\r\n", fd);
				return (-2);
			}
			else
			{
				haswithout = 1;
				i++;
			}
		}
		else if (with.find(str[i]) == std::string::npos && without.find(str[i]) == std::string::npos)
		{
				// check if it is a supported flag
			Server::sendResponse(":localhost 472 " + nick + " " + str[i] + " :is unknown mode char to me\r\n", fd);
			return (-2);
		}
		else if (with.find(str[i]) != std::string::npos && !(sign == '-' && str[i] == 'l'))
		{
			if (haswithout == 1) // flags without extra parameter cannot be before flags with extra parameter, otherwise there would be an alignment issue.
				return (-1);
			ret++;
		}
		else
			haswithout = 1;
		i++;
	}
	//return value is the number of flags with an extra parameter.
	return (ret);
}


void	setK(char sign, Channel *chan, std::string parameter)
{
	if (sign == 'p')
	{
		chan->setMode('k', 0);
		chan->setPassword(parameter);
	}
	else if (sign == 'n')
	{
		chan->setMode('k', 1);
		std::string	empty = "";
		chan->setPassword(empty);
	}
}


void	setO(char sign, Channel *chan, std::string parameter, int fd)
{
	if (sign == 'p')
	{
		chan->setMode('k', 0);
		chan->switchPrivilege(0, parameter, " MODE +o ", fd);
	}
	else if (sign == 'n')
	{
		std::string	empty = "";
		chan->switchPrivilege(1, parameter, " MODE -o ", fd);
	}
}

void	setL(char sign, Channel *chan, std::string parameter, int fd)
{
	if (sign == 'p')
	{
		for (size_t i = 0; i < parameter.size(); i++)
		{
			if (!(i == 0 && parameter[i] == '+'))
			{
				if (parameter[i] < 48 || parameter[i] > 57)
				{
					Server::sendResponse(":localhost 696 " + chan->get_admin(fd)->getNickName() + " MODE +l " + parameter + " :Invalid parameter\r\n", fd);
					return ;
				}
			}
		}
		int limit = ft_strtoi(parameter);
		chan->setMode('l', 0);
		chan->setLimit(limit);
	}
	else if (sign == 'n')
	{
		chan->setMode('l', 1);
		chan->setLimit(MAX_CLIENTS);
	}
}

void	setI(char sign, Channel *chan)
{
	if (sign == 'p')
	{
		chan->setMode('i', 0);
		chan->setInviteOnly(true);
	}
	else if (sign == 'n')
	{
		chan->setMode('i', 1);
		chan->setInviteOnly(false);
	}
}

void	setT(char sign, Channel *chan)
{
	if (sign == 'p')
	{
		chan->setMode('t', 0);
		chan->setTopicLimit(true);
	}
	else if (sign == 'n')
	{
		chan->setMode('t', 1);
		chan->setTopicLimit(false);
	}
}

void Server::mode(const std::string& arg, int fd)
{
	std::string	prefix = "#&+!";
	std::vector<std::string>	commands = splitString(arg, ' ');
	std::stringstream message;
	std::map <char, std::string>	positiveflags;
	std::map <char, std::string>	negativeflags;

	message.clear();
	//basic checks
	if ((commands.size() < 1))
	{
		sendResponse(":localhost 461 " + getClient(fd)->getNickName() + " MODE :Not enough parameters.\r\n", fd);
		return ;
	}
	if (prefix.find(commands[0][0]) == std::string::npos)
	{
		sendResponse(":localhost " + getClient(fd)->getNickName() + " MODE " + arg + " :User Mode not supported.\r\n", fd);
		return ;
	}
	if (!getChannel(commands[0]))
	{
		sendResponse(":localhost 403 " + getClient(fd)->getNickName() + " " + commands[0] + " :No such channel\r\n", fd);
		return ;
	}
	if (!getChannel(commands[0])->get_member(fd) || !getChannel(commands[0])->get_admin(fd))
	{
		sendResponse(":localhost 442 " + getClient(fd)->getNickName() + " " + commands[0] + " :The user is not on this channel.\r\n", fd);
		return ;
	}
	// send channel info back to client if there are no extra parameters
	if ((commands.size() == 1))
	{
		sendResponse(": 324 " + getClient(fd)->getNickName() + " " + commands[0] + " " + getChannel(commands[0])->getModes() + "\r\n" + \
					": 329 " + getClient(fd)->getNickName() + " " + commands[0] + " " + getChannel(commands[0])->getCreationTime() + "\r\n", fd);
		return ;
	}
	// check if the client has permission to modity the channel
	if (!getChannel(commands[0])->get_admin(fd))
	{
		sendResponse(":localhost 482 " + getClient(fd)->getNickName() + " " + commands[0] + " :You're not channel operator\r\n", fd);
		return ;
	}
	int	flagcheck = countFlags(commands[1], getClient(fd)->getNickName(), fd);
	//check if the basic structure of the flags is correct. 
	if (flagcheck < 0)
	{
		if (flagcheck == -1)
				sendResponse(":localhost 696 " + getClient(fd)->getNickName() + " MODE " + arg + " :Invalid parameter\r\n", fd);
		return ;
	}
	//check if the number of flags match the number of parameters after the flags
	if ((size_t)flagcheck != (commands.size() - 2))
	{
		sendResponse(":localhost 461 " + getClient(fd)->getNickName() + " MODE :Not enough parameters.\r\n", fd);
		return ;
	}

	size_t		i;
	int			count;
	std::string	with = "klo";

	i = 0;
	count = 2;
	// this while loop filling the maps with the flags
	while (i < commands[1].size())
	{
		if (commands[1][i] == '+') //in case of + symbol
		{
			if ((i + 1) >= commands[1].size())
				return ;
			i++;
			while (i < commands[1].size() && commands[1][i] != '+' && commands[1][i] != '-') //all the characters after + sign are +, until the next + or - sign is found
			{
				if ((positiveflags.find(commands[1][i]) == positiveflags.end()) && 
					(negativeflags.find(commands[1][i]) == negativeflags.end())) //check if the flag exists in one of the lists
				{
					if (with.find(commands[1][i]) != std::string::npos) // if the command is k or o or l, there will be an additional parameter
					{
						if (commands[1][i] == 'o' && !(getChannel(commands[0])->getMemberByNick(commands[count])) && !(getChannel(commands[0])->getAdminByNick(commands[count])))
						{
							//If the extra parameter (nickname) for +o does not exist in the channel, all the commands will not be executed
							sendResponse(":localhost 442 " + getClient(fd)->getNickName() + "MODE +o" + commands[count] + " :The user is not on this channel.\r\n", fd);
							sendResponse(":localhost 696 " + getClient(fd)->getNickName() + " MODE " + arg + " :Invalid parameter\r\n", fd);
							return ;
						}
						else if (commands[1][i] == 'l')
						{
							//If the extra parameter (limit on number of user) for +l is not a valid number, all the commands will not be executed
							for (size_t i = 0; i < commands[count].size(); i++)
							{
								if (!(i == 0 && commands[count][i] == '+'))
								{
									if (commands[count][i] < 48 || commands[count][i] > 57)
									{
										sendResponse(":localhost 696 " + getClient(fd)->getNickName() + " MODE +l " + commands[count] + " :Invalid parameter\r\n", fd);
										sendResponse(":localhost 696 " + getClient(fd)->getNickName() + " MODE " + arg + " :Invalid parameter\r\n", fd);
										return ;
									}

								}
							}
						}
						positiveflags[commands[1][i]] = commands[count];
					}
					else  // if the command is not k or o or l, there won't be an additional parameter, and the extra parameter is filled with empty string.
						positiveflags[commands[1][i]] = "";
					count++;
				}
				else
				{
					//multiple instances of the same flag is not valid
					sendResponse(":localhost 696 " + getClient(fd)->getNickName() + " " + arg + " :Invalid parameter\r\n", fd);
					return ;
				}
				i++;
			}
		}
		else if (commands[1][i] == '-')
		{
			if ((i + 1) >= commands[1].size()) //in case of - symbol
				return ;
			i++;
			while (i < commands[1].size() && commands[1][i] != '+' && commands[1][i] != '-') //all the characters after - sign are -, until the next + or - sign is found
			{
				if ((positiveflags.find(commands[1][i]) == positiveflags.end()) && 
					(negativeflags.find(commands[1][i]) == negativeflags.end())) //check if the flag exists in one of the lists
				{
					if (with.find(commands[1][i]) != std::string::npos && commands[1][i] != 'l')
					{
						if (commands[1][i] == 'o' && !(getChannel(commands[0])->getMemberByNick(commands[count])) && !(getChannel(commands[0])->getAdminByNick(commands[count])))
						{
							//If the extra parameter (nickname) for -o does not exist in the channel, all the commands will not be executed
							sendResponse(":localhost 442 " + getClient(fd)->getNickName() + "MODE -o" + commands[count] + " :The user is not on this channel.\r\n", fd);
							sendResponse(":localhost 696 " + getClient(fd)->getNickName() + " MODE " + arg + " :Invalid parameter\r\n", fd);
							return ;
						}
						negativeflags[commands[1][i]] = commands[count];
					}
					else
						negativeflags[commands[1][i]] = "";
					count++;
				}
				else
				{
					//multiple instances of the same flag is not valid
					sendResponse(":localhost 696 " + getClient(fd)->getNickName() + " MODE " + arg + " :Invalid parameter\r\n", fd);
					return ;
				}
				i++;
			}
		}
	}

	std::map <char, std::string>::iterator	it = positiveflags.begin();
	char	flags[] = {'k', 'l', 'o', 'i', 't'};
	int		j;
	while (it != positiveflags.end())
	{
		j = 0;
		while (j < 4 && flags[j] != it->first)
			j++;
		switch (j)
		{
		case	0:
				setK('p', getChannel(commands[0]), it->second);
				break ;
		case	1:
				setL('p', getChannel(commands[0]), it->second, fd);
				break ;
		case	2:
				setO('p', getChannel(commands[0]), it->second, fd);
				break ;
		case	3:
				setI('p', getChannel(commands[0]));
				break ;
		case	4:
				setT('p', getChannel(commands[0]));
				break ;
		default:
				//error message?
				break ;
		}
		it++;
	}
	it = negativeflags.begin();
	while (it != negativeflags.end())
	{
		j = 0;
		while (j < 4 && flags[j] != it->first)
			j++;
		switch (j)
		{
		case	0:
				setK('n', getChannel(commands[0]), it->second);
				break ;
		case	1:
				setL('n', getChannel(commands[0]), it->second, fd);
				break ;
		case	2:
				setO('n', getChannel(commands[0]), it->second, fd);
				break ;
		case	3:
				setI('n', getChannel(commands[0]));
				break ;
		case	4:
				setT('n', getChannel(commands[0]));
				break ;
		default:
				//error message?
				break ;
		}
		it++;
	}
	getChannel(commands[0])->broadcast(":localhost MODE " + arg + "\r\n", -1);
}
