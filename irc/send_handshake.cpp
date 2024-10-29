#include "server_class.hpp"
#include <string>

void Server::sendHandshake(int client_fd, const std::string &nickname)
{
    std::string welcome_msg = ":irc.example.com 001 " + nickname + " :Welcome to the IRC network, " + nickname + "!\r\n";
    send(client_fd, welcome_msg.c_str(), welcome_msg.length(), 0);
	return ;
}
