#include "irc.hpp"
#include "server_class.hpp"
#include <cerrno>
#include <csignal>
#include <poll.h>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>

bool	Server::registered(int fd)
{
	if (!getClient(fd) || getClient(fd)->getNickName().empty() || getClient(fd)->getUserName().empty() || getClient(fd)->getNickName() == "*")
		return (false);
	return (true);
}

void Server::acceptNewClient()
{
    Client		newClient;
    socklen_t	socklen;
    int			client_fd;

    if (this->getClientNumber() >= MAX_CLIENTS)
    {
        std::cerr << "Maximum number of clients reached. Refusing connection." << std::endl;
        return ;
    }
    memset(&this->_new_client_adr, 0, sizeof(this->_new_client_adr));
    socklen = sizeof(this->_new_client_adr);
    client_fd = accept(this->_socketfd, (sockaddr *)&(this->_new_client_adr), &socklen);
    if (client_fd == -1)
    {
        std::cerr << "Error accept(): " << std::strerror(errno) << std::endl;
        return ;
    }
    if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
    {
        std::cerr << "Error setting the socket as non-blocking: " << std::strerror(errno) << std::endl;
        return ;
    }
    this->_pollstruct.fd = client_fd;
    this->_pollstruct.events = POLLIN;
    this->_pollstruct.revents = 0;
    newClient.set_client_FD(client_fd);
    newClient.set_client_IP(inet_ntoa(this->_new_client_adr.sin_addr));
    this->_clientsList.push_back(newClient);
    this->_pollfds.push_back(this->_pollstruct);
    this->setClientNumber(this->getClientNumber() + 1);
    if (DEBUG == 1)
    {
        std::cout << "Client connected on FD: " << client_fd << std::endl;
        std::cout << "Client IP: " << inet_ntoa(this->_new_client_adr.sin_addr) << std::endl;
    }
    return ;
}
