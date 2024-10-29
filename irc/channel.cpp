#include "server_class.hpp"
#include "channel.hpp"
#include "irc.hpp"
#include "client_class.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class Server;

Channel::Channel(std::string name, std::string password, std::string topic)
	: _name(name), _password(password), _Topic(topic)
{
	_limit = MAX_CLIENTS;
	char	flags[] = {'k', 'l', 'o', 'i', 't'};
	_modeList.push_back(std::make_pair(flags[0], true));
	for (int i = 1; i < 5; i++)
		_modeList.push_back(std::make_pair(flags[i], false));
	return ;
}

Channel::Channel(std::string name, std::string topic)
	: _name(name), _password(""), _Topic(topic)
{
	_limit = MAX_CLIENTS;
	char	flags[] = {'k', 'l', 'o', 'i', 't'};
	for (int i = 0; i < 5; i++)
		_modeList.push_back(std::make_pair(flags[i], false));
	return ;
}

Channel::~Channel()
{
	return ;
}

const std::string &Channel::getName() const
{
	return (this->_name);
}

const std::string &Channel::getTopic() const
{
	return (this->_Topic);
}

const std::string &Channel::getTopicAuthor() const
{
	return (this->_TopicAuthor);
}

const std::string &Channel::getPassword() const
{
	return (this->_password);
}

void Channel::setTopic(const std::string &new_topic)
{
	this->_Topic = new_topic;
	return ;
}

void Channel::setTopicAuthor(const std::string &new_topic)
{
	this->_TopicAuthor = new_topic;
	return ;
}

void Channel::setPassword(std::string &new_pasword)
{
	this->_password = new_pasword;
	return ;
}

Client	*Channel::get_member(int fd)
{
	std::vector<Client *>::iterator it = _membersList.begin(); 
	while (it != _membersList.end())
	{
		if ((*it)->get_client_FD() == fd)
			return &(**it);
		it++;
	}
	return (NULL);
}
Client	*Channel::get_admin(int fd)
{
	std::vector<Client *>::iterator it = _adminsList.begin(); 
	while (it != _adminsList.end())
	{
		if ((*it)->get_client_FD() == fd)
			return &(**it);
		it++;
	}
	return (NULL);
}

Client	*Channel::getMemberByNick(std::string name)
{
	std::vector<Client *>::iterator it = _membersList.begin(); 
	while (it != _membersList.end())
	{
		if ((*it)->getNickName() == name)
			return &(**it);
		it++;
	}
	return (NULL);
}


Client	*Channel::getAdminByNick(std::string name)
{
	std::vector<Client *>::iterator it = _adminsList.begin(); 
	while (it != _adminsList.end())
	{
		if ((*it)->getNickName() == name)
			return &(**it);
		it++;
	}
	return (NULL);
}


bool	Channel::getInviteOnly()
{
	return (this->_inviteOnly);
}

void	Channel::setInviteOnly(bool inviteOnly)
{
	this->_inviteOnly = inviteOnly;
	return ;
}

bool	Channel::getTopicLimit()
{
	return (this->_topicLimit);
}

void	Channel::setTopicLimit(bool limit)
{
	this->_topicLimit = limit;
	return ;
}

int	Channel::getLimit()
{
	return (this->_limit);
}

void	Channel::setLimit(int limit)
{
	this->_limit = limit;
	return ;
}

int Channel::getNumberOfClients()
{
	return (this->_membersList.size() + this->_adminsList.size());
}

void Channel::addInviteList(Client *cli)
{
	if (!isInvited(cli))
		_inviteList.push_back(cli);
	return ;
}

bool Channel::isInvited(Client *cli) const
{
	for (size_t i = 0; i < _inviteList.size(); ++i)
	{
		if (_inviteList[i]->get_client_FD() == cli->get_client_FD())
			return (true);
	}
	return (false);
}

void Channel::removeInvite(Client *cli)
{
    for (size_t i = 0; i < _inviteList.size(); ++i)
    {
        if (_inviteList[i]->get_client_FD() == cli->get_client_FD())
        {
            _inviteList.erase(_inviteList.begin() + i);
            break;
        }
    }
	return ;
}

void	Channel::broadcast(const std::string& str, int except)
{
	std::vector<Client *>::iterator it = _membersList.begin(); 
	while (it != _membersList.end())
	{
		if ((*it)->get_client_FD() != except)
			Server::sendResponse(str, (*it)->get_client_FD());
		it++;
	}
	it = _adminsList.begin(); 
	while (it != _adminsList.end())
	{
		if ((*it)->get_client_FD() != except)
			Server::sendResponse(str, (*it)->get_client_FD());
		it++;
	}
	return ;
}

void	Channel::removeByNick(const std::string& str)
{
	std::vector<Client *>::iterator it = _membersList.begin(); 
	while (it != _membersList.end())
	{
		if ((*it)->getNickName() == str)
		{
			_membersList.erase(it);
			return ;
		}
		it++;
	}
	it = _adminsList.begin(); 
	while (it != _adminsList.end())
	{
		if ((*it)->getNickName() == str)
		{
			_adminsList.erase(it);
			return ;
		}
		it++;
	}
	return ;
}

void	Channel::setCreationTime()
{
	std::time_t _time = std::time(NULL);
	std::ostringstream oss;
	oss << _time;
	this->_creationTime = std::string(oss.str());
}


std::string		Channel::getCreationTime()
{
	return (_creationTime);
}

void	Channel::setTopicTime()
{
	std::time_t _time = std::time(NULL);
	std::ostringstream oss;
	oss << _time;
	this->_topicTime = std::string(oss.str());
}


std::string		Channel::getTopicTime()
{
	return (_topicTime);
}

std::string Channel::getModes()
{
	std::string	ret = "";
	size_t		i;

	i = 0;
	while (i < _modeList.size())
	{
		if(_modeList[i].first != 'o' && _modeList[i].second)
			ret.push_back(_modeList[i].first);
		i++;
	}
	if(!ret.empty())
		ret.insert(ret.begin(), '+');
	return (ret);
}

void	Channel::setMode(char flag, int	sign)
{
	std::vector<std::pair<char, bool> >::iterator it = _modeList.begin();
    while (it != _modeList.end())
    {
        if (it->first == flag)
        {
        	if (sign == 0)
        		it->second = true;
        	else if (sign == 1)
        		it->second = false;
        	return ;
        }
        it++;
    }
}

bool Channel::isMember(Client *client) const
{
	return (std::find(_membersList.begin(), _membersList.end(), client) != _membersList.end());
}

bool Channel::isAdmin(Client *client) const
{
	return (std::find(_adminsList.begin(), _adminsList.end(), client) != _adminsList.end());
}

bool Channel::isMemberCombined(Client *client) const
{
	return (isMember(client) || isAdmin(client));
}

int	Channel::switchPrivilege(int dir, std::string nick, std::string command, int fd)
{
	if (dir == 0) //add user to operator list
	{
		if (getAdminByNick(nick))
			return (0);
		Client *user = getMemberByNick(nick);
		if (!user)
		{
			Server::sendResponse(":localhost 442 " + get_admin(fd)->getNickName() + command + nick + " :The user is not on this channel.\r\n", fd);
			return (-1);
		}
		removeByNick(nick);
		_adminsList.push_back(user);
		return (0);
	}
	if (dir == 1) //remove user from operator list
	{
		if (getMemberByNick(nick))
			return (0);
		Client *user = getAdminByNick(nick);
		if (!user)
		{
			Server::sendResponse(":localhost 442 " + get_admin(fd)->getNickName() + command + nick + " :The user is not on this channel.\r\n", fd);
			return (-1);
		}
		removeByNick(nick);
		_membersList.push_back(user);
		return (0);
	}
	return (1);
}
