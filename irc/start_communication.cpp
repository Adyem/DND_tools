#include "irc.hpp"
#include "server_class.hpp"
#include <cerrno>
#include <csignal>
#include <poll.h>
#include <stdexcept>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>

void Server::ft_start_server()
{
    size_t i;

    std::signal(SIGINT, Server::stop);
    while (this->_running)
    {
        int poll_result = poll(&this->_pollfds[0], this->_pollfds.size(), 500);
        if (poll_result == -1)
        {
            if (!this->_running)
                return;

            if (DEBUG == 1)
                std::cerr << "poll failed: " << std::strerror(errno) << std::endl;
            throw std::runtime_error("poll failed");
        }
        i = 0;
        while (i < this->_pollfds.size())
        {
            if (this->_pollfds[i].revents & POLLIN)
            {
                if (this->_pollfds[i].fd == this->_socketfd)
                {
                    if (DEBUG == 1)
                        std::cout << "Incoming connection on server socket" << std::endl;
                    this->acceptNewClient();
                }
                else
                {
                    if (DEBUG == 1)
                        std::cout << "Incoming data from client socket: " << this->_pollfds[i].fd << std::endl;
                    this->receiveNewData(this->_pollfds[i].fd);
                }
            }
			ft_sendPing(this->_pollfds[i].fd);
            if (ft_check_pong(this->_pollfds[i].fd))
            {
                if (DEBUG == 1)
                    std::cout << "Client on FD " << this->_pollfds[i].fd << " did not respond to PING, disconnecting." << std::endl;
				ft_quit(":Ping timeout", this->_pollfds[i].fd);
                continue ;
            }
            i++;
        }
    }
    return ;
}
