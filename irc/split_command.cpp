#include "server_class.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <utility>

std::pair<std::string, std::string> Server::splitCommand(const std::string& commandStr)
{
    std::istringstream iss(commandStr);
    std::string command, argument;
    iss >> command;
    std::getline(iss, argument);
    argument.erase(0, argument.find_first_not_of(' '));

    return (std::make_pair(command, argument));
}

std::vector<std::string> Server::splitString(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter))
    {
        tokens.push_back(item);
    }
    return (tokens);
}

std::vector<std::pair<std::string, std::string> > Server::processBuffer(char buffer[])
{
    std::string input(buffer);
    std::vector<std::string> commands = splitString(input, '\n');
    std::vector<std::pair<std::string, std::string> > parsedCommands;
	for (std::vector<std::string>::iterator it = commands.begin(); it != commands.end(); ++it)
	{
		std::string& commandStr = *it;
		if (!commandStr.empty() && commandStr[commandStr.length() - 1] == '\r')
            commandStr.erase(commandStr.length() - 1);
		if (!commandStr.empty())
	        parsedCommands.push_back(splitCommand(commandStr));
	}
    return (parsedCommands);
}
