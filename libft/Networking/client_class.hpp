#ifndef FT_CLIENT_H
#define FT_CLIENT_H

#include "../CPP_class/string.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <atomic>
#include <unistd.h>
#include <cstring>

class ft_client
{
	public:
    	explicit ft_client(int client_fd);

    	~ft_client();
    	ft_client(const ft_client&) = delete;
    	ft_client& operator=(const ft_client&) = delete;
    	ft_client(ft_client&& other) noexcept;
    	ft_client& operator=(ft_client&& other) noexcept;

    	ssize_t send_data(const void* data, size_t size, int flags = 0);
    	ssize_t receive_data(void* buffer, size_t size, int flags = 0);
    	void close_connection();
    	bool is_closed() const;
    	int get_fd() const;
		void set_error(int error);
    	ft_string get_client_address() const;

	private:
		int _error;
	    int client_fd;
	    std::atomic<bool> closed;
	    struct sockaddr_storage client_addr;
	    void retrieve_client_address();
};

#endif
