#ifndef SERVER_CLASS_HPP
# define SERVER_CLASS_HPP

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h> 
#include <vector>
#include "client_class.hpp"
#include "channel.hpp"

class Server
{
	private:
		sockaddr_in					_server_adr;
		sockaddr_in					_new_client_adr;
		const int					_socketfd;
		std::string					_password;
		std::vector<struct pollfd>	_pollfds;
		struct pollfd				_pollstruct;
		std::vector<Client>			_clientsList;
		static volatile bool		_running;
		int							_client_number;
		std::vector<Channel>		_channelsList;

	private:
		Channel		*getChannelByName(const std::string &channelName);
		void		sendHandshake(int client_fd, const std::string &nickname);
		void		acceptNewClient();
		void		receiveNewData(int fd);
		std::vector<std::string> splitString(const std::string& str, char delimiter);
		std::pair<std::string, std::string> splitCommand(const std::string& commandStr);
		std::vector<std::pair<std::string, std::string> > processBuffer(char buffer[]);
		void		exec_parsed_cmd(const std::string &cmd, const std::string &arg, int fd);
		void		check_pw(const std::string &arg, int fd);
		void		set_username(const std::string& arg, int fd);
		bool		nicknameInUse(const std::string& nickname);
		bool		is_validNickname(std::string& nickname);
		void		set_nickname(const std::string& arg, int fd);
		void		broadcastNickChange(const std::string& oldNick, const std::string& newNick);
		void		ft_pong(int fd);
		void		ft_sendPing(int fd);
		int			ft_check_pong(int fd);
		void		ft_quit(const std::string &arg, int fd);
		void		ft_send_pong(const std::string &arg, int fd);
		void		cap(const std::string &arg, int fd);
		void		privmsg(const std::string& arg, int fd);
		Client		*getClient(int fd);
		Client		*getClientByNickname(std::string nickname);
		bool		registered(int fd);
		const int	&getClientNumber() const;
		void		setClientNumber(int new_number_of_clients);
		Channel		*getChannel(std::string name);
		void		invite(const std::string& arg, int fd);
		void		kick(const std::string& arg, int fd);
		void		part(const std::string& arg, int fd);
		void		mode(const std::string& arg, int fd);
		void		topic(const std::string& arg, int fd);
		void		ft_join(const std::string &arg, int fd);
		void		ft_notice(const std::string &arg, int fd);
	
	public:
					Server(int port_number, std::string password);
					~Server();
		const int	&getSocketfd() const;
		void		ft_start_server();
		static void	stop(int signal);
		void static	sendResponse(std::string response, int fd);
};

#endif
