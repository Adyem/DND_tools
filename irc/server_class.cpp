#include "server_class.hpp"
#include <cstddef>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <poll.h> 
#include <fcntl.h>
#include <vector>
#include <iostream>
#include <csignal>
#include <string>

volatile bool	Server::_running = true;

Server::Server(int port_number, std::string password) : _socketfd(socket(AF_INET, SOCK_STREAM, 0)), _password(password)
{
	int		en;

	_client_number = 0;
	if (this->_socketfd == -1)
		return ;
	en = 1;
	this->_server_adr.sin_family = AF_INET;
	this->_server_adr.sin_addr.s_addr = INADDR_ANY;
	this->_server_adr.sin_port = htons(port_number);
	if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
	{
		close(this->_socketfd);
		throw(std::runtime_error("Error setting set the socket reusing busy ports without waiting"));
	}
	if (fcntl(this->_socketfd, F_SETFL, O_NONBLOCK) == -1)
	{
		close(this->_socketfd);
		throw(std::runtime_error("Error setting the socket as non-blocking"));
	}
	if (bind(this->_socketfd, (struct sockaddr *)&this->_server_adr, sizeof(this->_server_adr)) < 0)
	{
		close(this->_socketfd);
		throw std::runtime_error("Error binding socket");
	}
	if (listen(this->_socketfd, SOMAXCONN) == -1)
	{
		close(this->_socketfd);
		throw(std::runtime_error("Error listen()"));
	}
	this->_pollstruct.fd = _socketfd;
	this->_pollstruct.events = POLLIN;
	this->_pollstruct.revents = 0;
	this->_pollfds.push_back(_pollstruct);
	return ;
}

Server::~Server()
{
	close(this->_socketfd);
	return ;
}

Client	*Server::getClient(int fd)
{
	size_t	i;

	i = 0;
	while (i < this->_clientsList.size())
	{
		if (this->_clientsList[i].get_client_FD() == fd)
			return (&this->_clientsList[i]);
		i++;
	}
	return (NULL);
}

Client	*Server::getClientByNickname(std::string nickname)
{
	size_t	i;

	i = 0;
	while (i < this->_clientsList.size())
	{
		if (this->_clientsList[i].getNickName() == nickname)
			return (&this->_clientsList[i]);
		i++;
	}
	return (NULL);
}

const int	&Server::getClientNumber() const
{
	return (this->_client_number);
}

void	Server::setClientNumber(int new_number_of_clients)
{
	this->_client_number = new_number_of_clients;
	return ;
}

const int	&Server::getSocketfd() const
{
	return (this->_socketfd);
}

void	Server::stop(int signal)
{
    if (signal == SIGINT || signal == SIGTERM)
    {
        std::cout << std::endl << "Received signal: " << signal << ", stopping server..." << std::endl;
        _running = false;
    }
    else
        std::cout << "Received unhandled signal: " << signal << std::endl;
    return ;
}



Channel	*Server::getChannel(std::string name)
{
	size_t	i;

	i = 0;
	while (i < this->_channelsList.size())
	{
		if (this->_channelsList[i].getName() == name)
			return (&_channelsList[i]);
		i++;
	}
	return (NULL);
}

Channel *Server::getChannelByName(const std::string &channelName)
{
	size_t	i = 0;
	while (i < _channelsList.size())
	{
		if (_channelsList[i].getName() == channelName)
			return &_channelsList[i];
		i++;
	}
	return (NULL);
}
