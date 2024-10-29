#ifndef CLIENT_CLASS_HPP
# define CLIENT_CLASS_HPP

#include <ctime>
#include <poll.h>
#include <string>

class Client
{
	private:
		int			_client_fd;
		std::string	_client_ip;
		std::string	_nickname;
		std::string	_username;
		bool		_registered;
		bool		_loggedin;
		std::time_t	_timeping;
		std::time_t	_timepong;

	public:
		Client();
		~Client();
		void				set_client_FD(int newfd);
		int					get_client_FD(void) const;
		void				set_client_IP(const std::string ip);
		std::string			getNickName();
		void				setNickName(const std::string& nickname);
		std::string			getUserName();
		void				setUserName(const std::string& username);
		bool				getRegistered();
		void				setRegistered(bool status);
		bool				getLoggedIn();
		void				setLoggedin(bool value);
		const std::time_t	&getTimePing() const;
		const std::time_t	&getTimePong() const;
		void				setTimePing(const std::time_t &new_time);
		void				setTimePong(const std::time_t &new_time);
};

#endif
