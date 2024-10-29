#include <poll.h>
#include "client_class.hpp"
#include <ctime>

Client::Client() : _client_fd(-1), _client_ip(""), _nickname(""), _username(""), _registered(false), _loggedin(false)
{
	_timeping = std::time(NULL);
	_timepong = std::time(NULL);
	return ;
}

Client::~Client()
{
	return ;
}

void	Client::set_client_FD(int newfd)
{
	this->_client_fd = newfd;
	return ;
}

int	Client::get_client_FD(void) const
{
	return (_client_fd);
}

void	Client::set_client_IP(const std::string ip)
{
	this->_client_ip = ip;
	return ;
}

std::string	Client::getNickName()
{
	return (this->_nickname);
}

void	Client::setNickName(const std::string& nickname)
{
	this->_nickname = nickname;
	return ;
}

std::string	Client::getUserName()
{
	return (this->_username);
}

void	Client::setUserName(const std::string& username)
{
	this->_username = username;
	return ;
}

bool	Client::getRegistered()
{
	return (_registered);
}

void	Client::setRegistered(bool status)
{
	_registered = status;
	return ;
}

bool	Client::getLoggedIn()
{
	return (this->_loggedin);
}

void	Client::setLoggedin(bool value)
{
	this->_loggedin = value;
	return ;
}

const std::time_t &Client::getTimePing() const
{
	return (this->_timeping);
}

const std::time_t &Client::getTimePong() const
{
	return (this->_timepong);
}

void	Client::setTimePing(const std::time_t &new_time)
{
	this->_timeping = new_time;
	return ;
}

void	Client::setTimePong(const std::time_t &new_time)
{
	this->_timepong = new_time;
	return ;
}
