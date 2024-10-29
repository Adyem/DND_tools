#include "server_class.hpp"

void	Server::invite(const std::string& arg, int fd)
{
	std::string	prefix = "#&+!";
	std::vector<std::string>	commands = splitString(arg, ' ');

	if ((commands.size() < 2))
	{
		sendResponse(":localhost 461 " + getClient(fd)->getNickName() + " INVITE :Not enough parameters.\r\n", fd);
		return;
	}
	//in case of non-existing channel
	if (prefix.find(commands[1][0]) == std::string::npos || !getChannel(commands[1]))
	{
		sendResponse(":localhost 403 " + getClient(fd)->getNickName() + " #" + commands[1] + " :No such channel\r\n", fd);
		return;
	}
	//if the client is not member or admin of the channel
	if (!(getChannel(commands[1])->get_member(fd)) && !(getChannel(commands[1])->get_admin(fd)))
	{
		sendResponse(":localhost 442 " + getClient(fd)->getNickName() + " #" + commands[1] + " :The user is not on this channel.\r\n", fd);
		return;
	}
	// if the target is already member of the channel
	if (getChannel(commands[1])->getMemberByNick(commands[0]) || getChannel(commands[1])->getAdminByNick(commands[0]))
	{
		sendResponse(":localhost 443 " + getClient(fd)->getNickName() + " " + commands[0] + " #" + commands[1] + " :Is already on channel\r\n", fd);
		return;
	}
	//if there are not any existing client with the given nickname
	if (!getClientByNickname(commands[0]))
	{
		sendResponse(":localhost 401 " + getClient(fd)->getNickName() + " " + commands[0] + " :No such nick/channel\r\n", fd);
		return;
	}
	// Only operator can invite on invite-only channel
	if (getChannel(commands[1])->getInviteOnly() && !getChannel(commands[1])->get_admin(fd))
	{
		sendResponse(":localhost 482 " + getClient(fd)->getNickName() + " #" + commands[1] + " :You're not channel operator\r\n", fd);
		return;
	}
	// channel is full
	if (getChannel(commands[1])->getLimit() && getChannel(commands[1])->getNumberOfClients() >= getChannel(commands[1])->getLimit())
	{
		sendResponse(":localhost 471 " + getClient(fd)->getNickName() + " #" + commands[1] + " :Cannot join channel (+l)\r\n", fd);
		return;
	}
	// Add client to invitation list
	getChannel(commands[1])->addInviteList(getClientByNickname(commands[0]));
	//send message to both invitor and invitee
	sendResponse(":localhost INVITE " + commands[0] + " #" + commands[1] + "\r\n", getClientByNickname(commands[0])->get_client_FD());
	sendResponse(": 341 " + getClient(fd)->getNickName() + " #" + commands[1] + " " + commands[0] + " :Invite sent\r\n", fd);
}