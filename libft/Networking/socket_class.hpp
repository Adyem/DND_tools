#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include "networking.hpp"

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
		int create_socket(const SocketConfig &config);
    	int set_reuse_address(const SocketConfig &config);
    	int set_non_blocking(const SocketConfig &config);
    	int set_timeouts(const SocketConfig &config);
    	int configure_address(const SocketConfig &config, struct sockaddr_storage &addr);
    	int bind_socket(const struct sockaddr_storage &addr, const SocketConfig &config);
    	int listen_socket(const SocketConfig &config);
    	void handle_error(int error_code);
	
    	int socket_fd;
    	int _error;
    	int setup_server(const SocketConfig &config);
    	int setup_client(const SocketConfig &config);

    	ft_socket(const ft_socket &other) = delete;
		ft_socket(ft_socket &&other) = delete;
    	ft_socket &operator=(const ft_socket &other) = delete;
		ft_socket &operator=(ft_socket &&other) = delete;
};

#endif
