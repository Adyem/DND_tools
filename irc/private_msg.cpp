#include "server_class.hpp"
#include "channel.hpp"

void Server::privmsg(const std::string& arg, int fd)
{
    size_t pos = arg.find(" :");
    if (pos == std::string::npos)
    {
        this->sendResponse("412 :No text to send\r\n", fd);
        return ;
    }
    std::string targets_str = arg.substr(0, pos);
    std::string message = arg.substr(pos + 2);
    targets_str.erase(0, targets_str.find_first_not_of(" \t"));
    targets_str.erase(targets_str.find_last_not_of(" \t") + 1);
    if (targets_str.empty())
    {
        this->sendResponse("411 :No recipient given (PRIVMSG)\r\n", fd);
        return ;
    }
    std::vector<std::string> targets = this->splitString(targets_str, ',');
    Client *sender = this->getClient(fd);
    if (!sender)
    {
        this->sendResponse("Error: Sender not found\r\n", fd);
        return ;
    }
    std::string prefix = ":" + sender->getNickName() + "!" + sender->getUserName() + "@localhost PRIVMSG ";
    for (size_t i = 0; i < targets.size(); ++i)
    {
        std::string target = targets[i];
        target.erase(0, target.find_first_not_of(" \t"));
        target.erase(target.find_last_not_of(" \t") + 1);
        if (target.empty())
            continue ;
        if (target[0] == '#')
        {
            Channel *channel = getChannel(target);
            if (channel == NULL)
                this->sendResponse("403 " + target + " :No such channel\r\n", fd);
            else
            {
                if (!channel->isMember(sender) && !channel->isAdmin(sender))
                {
                    this->sendResponse("442 " + target + " :You're not on that channel\r\n", fd);
                    continue ;
                }
                std::string fullMessage = prefix + target + " :" + message + "\r\n";
				channel->broadcast(fullMessage, fd);
            }
        }
        else
        {
            Client *client = this->getClientByNickname(target);
            if (client == NULL)
                this->sendResponse("401 " + target + " :No such nick/channel\r\n", fd);
            else
            {
                std::string fullMessage = prefix + target + " :" + message + "\r\n";
                this->sendResponse(fullMessage, client->get_client_FD());
            }
        }
    }
}
