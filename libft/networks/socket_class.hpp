#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include "../Errno/errno.hpp"
#include <string>

enum class SocketType {
    SERVER,
    CLIENT,
    RAW // For other specialized uses
};

struct SocketConfig {
    SocketType type;
    std::string ip;
    int port;
    int backlog; // Relevant for server sockets
    // Add other configuration parameters as needed
};

class ft_socket {
public:
    // Constructor that takes a configuration struct
    ft_socket(const SocketConfig &config);

    // Destructor
    ~ft_socket();

    // Methods
    ssize_t send_data(const void *data, size_t size, int flags = 0);
    ssize_t receive_data(void *buffer, size_t size, int flags = 0);
    bool close_socket();

    // Error handling
    int get_error() const; // Returns the local error code
    const char* get_error_message() const; // Returns the error message

    // Additional utility methods can be added here

private:
    int sock_fd = -1;
    int _error = static_cast<int>(FT_Error::NONE); // Local error variable

    void setup_server(const std::string &ip, int port, int backlog);
    void setup_client(const std::string &ip, int port);

    // Disallow copy and assignment
    ft_socket(const ft_socket&) = delete;
    ft_socket& operator=(const ft_socket&) = delete;
};

#endif // FT_SOCKET_H
