#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include "../Errno/errno.hpp"
#include <string>

enum class SocketType {
    SERVER,
    CLIENT,
    RAW
};

struct SocketConfig {
    SocketType type;
    std::string ip;
    int port;
    int backlog;
};

class ft_socket
{
	public:
    	ft_socket(const SocketConfig &config);

    	~ft_socket();

    	ssize_t send_data(const void *data, size_t size, int flags = 0);
    	ssize_t receive_data(void *buffer, size_t size, int flags = 0);
    	bool close_socket();

    	int get_error() const;
    	const char* get_error_message() const;


	private:
    	int sock_fd = -1;
    	int _error = ER_SUCCESS;

    	void setup_server(const std::string &ip, int port, int backlog);
    	void setup_client(const std::string &ip, int port);

    	ft_socket(const ft_socket&) = delete;
    	ft_socket& operator=(const ft_socket&) = delete;
};

#endif
