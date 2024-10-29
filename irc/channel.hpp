#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <vector>

class Client;

class Channel
{
	private:
		std::string				_name;
		std::string				_password;
		std::string				_Topic;
		std::string				_TopicAuthor;
		std::vector<Client*>	_membersList;
		std::vector<Client*>	_adminsList;
		std::vector<Client*>	_inviteList;
		bool					_inviteOnly;
		bool					_topicLimit;
		int						_limit;
		std::string				_creationTime;
		std::string				_topicTime;
		std::vector<std::pair<char, bool> >	_modeList;
		Channel(Channel const &src);
		Channel &operator=(Channel const &other);
		Channel();

	public:
		Channel(std::string name, std::string topic, std::string password);
		Channel(std::string name, std::string topic);
		~Channel();
		const std::string	&getName() const;
		const std::string	&getTopic() const;
		const std::string	&getTopicAuthor() const;
		const std::string	&getPassword() const;
		void				setTopic(const std::string &new_topic);
		void				setTopicAuthor(const std::string &new_topic);
		void				setPassword(std::string &new_password);
		Client				*get_member(int fd);
		Client				*get_admin(int fd);
		Client				*getMemberByNick(std::string name);
		Client				*getAdminByNick(std::string name);
		bool				getInviteOnly();
		void				setInviteOnly(bool inviteOnly);
		bool				getTopicLimit();
		void				setTopicLimit(bool limit);
		int					getLimit();
		void				setLimit(int limit);
		int					getNumberOfClients();
		void				addInviteList(Client *cli);
		bool				isInvited(Client *cli) const;
		void				broadcast(const std::string& str, int except);
		void				removeInvite(Client *cli);
		void				removeByNick(const std::string& str);
		std::string			getCreationTime();
		void				setCreationTime();
		std::string			getTopicTime();
		void				setTopicTime();
		std::string			getModes();
		bool				isMember(Client *client) const;
		bool				isAdmin(Client *client) const;
		bool				isMemberCombined(Client *client) const;
		void				setMode(char flag, int	sign);
		int					switchPrivilege(int dir, std::string nick, std::string command,
												int fd);
		int					addMember(Client* client);
};

#endif
