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

void Server::receiveNewData(int fd)
{
    char	buffer[1024];
    ssize_t bytesRead;

	bytesRead = recv(fd, buffer, sizeof(buffer) - 1, 0);
    if (DEBUG == 1)
        std::cout << "Received data from client FD " << fd << ": " << buffer << std::endl;
    if (bytesRead == -1)
    {
        std::cerr << "Error reading from socket FD " << fd << ": " << std::strerror(errno) << std::endl;
        return ;
    }
    else if (bytesRead == 0)
    {
        std::cout << "Client on FD " << fd << " disconnected" << std::endl;
        close(fd);
        return ;
    }
    buffer[bytesRead] = '\0';
    std::vector<std::pair<std::string, std::string> > result = processBuffer(buffer);
	for (std::vector<std::pair<std::string, std::string> >::const_iterator it = result.begin(); it != result.end(); ++it)
	{
		if (DEBUG == 1)
			std::cout << "Command: " << it->first << ", Argument: " << it->second << std::endl;
		this->exec_parsed_cmd(it->first, it->second, fd);
	}
}

void	Server::sendResponse(std::string response, int fd)
{
	if (response.empty())
		return ;
	size_t		totalSent = 0;
	size_t		responseSize = response.size();
	const char*	responseData = response.c_str();
	while (totalSent < responseSize)
	{
		ssize_t bytesSent = send(fd, responseData + totalSent, responseSize - totalSent, 0);
		if (bytesSent == -1)
		{
			std::cerr << "Error sending response" << std::endl;
			return ;
		}
		totalSent += bytesSent;
	}
	return ;
}
