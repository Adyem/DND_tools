#include "server_class.hpp"
#include <string>
#include <cctype>

static std::string to_uppercase(const std::string &str)
{
    std::string upper_str = str;
	std::size_t i = 0;
    while (i < upper_str.length())
	{
        upper_str[i] = std::toupper(static_cast<unsigned char>(upper_str[i]));
		i++;
	}
    return (upper_str);
}

void	Server::exec_parsed_cmd(const std::string &cmd, const std::string &arg, int fd)
{
	if (cmd.empty())
		return ;
	std::string cmd_upper = to_uppercase(cmd);
	if (cmd_upper == "PONG")
		ft_pong(fd);
	else if (cmd_upper == "CAP")
		cap(arg, fd);
	else if (cmd_upper == "PASS")
		check_pw(arg, fd);
	else if (cmd_upper == "NICK")
		set_nickname(arg,fd);
	else if (cmd_upper == "USER")
		set_username(arg, fd);
	else if (cmd_upper == "QUIT")
		ft_quit(arg, fd);
	else if (registered(fd))
	{
		if (cmd_upper == "PING")
			 ft_send_pong(arg, fd);
		else if (cmd_upper == "INVITE")
			invite(arg,fd);
		else if (cmd_upper == "KICK")
			kick(arg, fd);
		else if (cmd_upper == "JOIN")
			ft_join(arg, fd);
		else if (cmd_upper == "MODE")
			mode(arg, fd);
		else if (cmd_upper == "PART")
			part(arg, fd);
		else if (cmd_upper == "PRIVMSG")
			privmsg(arg, fd);
		else if (cmd_upper == "TOPIC")
			topic(arg, fd);
		else
			sendResponse(getClient(fd)->getNickName() + ": Unknown command '" + cmd + "'.\r\n", fd);
	}
	else if (!registered(fd))
		sendResponse("You have not registered correctly or unknown command.\r\n", fd);
	return ;
}
