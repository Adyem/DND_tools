#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include "networking.hpp"
#include "../Errno/errno.hpp"
#include "../CPP_class/string.hpp"

class ft_socket
{
	public:
    	ft_socket(const SocketConfig &config);
    	~ft_socket();
    	int send_data(const void *data, size_t size, int flags = 0);
    	int receive_data(void *buffer, size_t size, int flags = 0);
    	bool close_socket();
    	int get_error() const;
    	const char* get_error_message() const;

	private:
    	int sock_fd = -1;
    	int _error = ER_SUCCESS;
    	void setup_server(const ft_string &ip, int port, int backlog);
    	void setup_client(const ft_string &ip, int port);

    	ft_socket(const ft_socket &other) = delete;
		ft_socket(ft_socket &&other) = delete;
    	ft_socket &operator=(const ft_socket &other) = delete;
		ft_socket &operator=(ft_socket &&other) = delete;
};

#endif
