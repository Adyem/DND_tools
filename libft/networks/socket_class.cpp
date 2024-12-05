#include "socket_class.hpp"
#include "../Errno/errno.hpp"
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

// Constructor
ft_socket::ft_socket(const SocketConfig &config) {
    if (config.type == SocketType::SERVER) {
        setup_server(config.ip, config.port, config.backlog);
    } else if (config.type == SocketType::CLIENT) {
        setup_client(config.ip, config.port);
    } else {
        // Handle other types or set error
        _error = static_cast<int>(FT_Error::UNSUPPORTED_SOCKET_TYPE);
    }
}

// Destructor
ft_socket::~ft_socket() {
    if (sock_fd >= 0) {
        close(sock_fd);
    }
}

// Setup server
void ft_socket::setup_server(const std::string &ip, int port, int backlog) {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        _error = static_cast<int>(FT_Error::SOCKET_CREATION_FAILED);
        set_ft_errno(static_cast<FT_Error>(FT_Error::SOCKET_CREATION_FAILED));
        return;
    }

    // Set socket options (optional)
    int opt = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        _error = static_cast<int>(FT_Error::SOCKET_CREATION_FAILED); // You may define a specific error
        set_ft_errno(static_cast<FT_Error>(FT_Error::SOCKET_CREATION_FAILED));
        close(sock_fd);
        sock_fd = -1;
        return;
    }

    // Bind
    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0) {
        _error = static_cast<int>(FT_Error::INVALID_IP_FORMAT);
        set_ft_errno(static_cast<FT_Error>(FT_Error::INVALID_IP_FORMAT));
        close(sock_fd);
        sock_fd = -1;
        return;
    }

    if (::bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        _error = static_cast<int>(FT_Error::SOCKET_BIND_FAILED);
        set_ft_errno(static_cast<FT_Error>(FT_Error::SOCKET_BIND_FAILED));
        close(sock_fd);
        sock_fd = -1;
        return;
    }

    // Listen
    if (::listen(sock_fd, backlog) < 0) {
        _error = static_cast<int>(FT_Error::SOCKET_LISTEN_FAILED);
        set_ft_errno(static_cast<FT_Error>(FT_Error::SOCKET_LISTEN_FAILED));
        close(sock_fd);
        sock_fd = -1;
        return;
    }

    // If everything succeeded, ensure _error is NONE
    _error = static_cast<int>(FT_Error::NONE);
}

// Setup client
void ft_socket::setup_client(const std::string &ip, int port) {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        _error = static_cast<int>(FT_Error::SOCKET_CREATION_FAILED);
        set_ft_errno(static_cast<FT_Error>(FT_Error::SOCKET_CREATION_FAILED));
        return;
    }

    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
        _error = static_cast<int>(FT_Error::INVALID_IP_FORMAT);
        set_ft_errno(static_cast<FT_Error>(FT_Error::INVALID_IP_FORMAT));
        close(sock_fd);
        sock_fd = -1;
        return;
    }

    if (::connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        _error = static_cast<int>(FT_Error::SOCKET_CONNECT_FAILED);
        set_ft_errno(static_cast<FT_Error>(FT_Error::SOCKET_CONNECT_FAILED));
        close(sock_fd);
        sock_fd = -1;
        return;
    }

    // If everything succeeded, ensure _error is NONE
    _error = static_cast<int>(FT_Error::NONE);
}

// Send data
ssize_t ft_socket::send_data(const void *data, size_t size, int flags) {
    if (sock_fd < 0) {
        _error = static_cast<int>(FT_Error::SOCKET_CREATION_FAILED);
        set_ft_errno(static_cast<FT_Error>(FT_Error::SOCKET_CREATION_FAILED));
        return -1;
    }

    ssize_t bytes_sent = send(sock_fd, data, size, flags);
    if (bytes_sent < 0) {
        _error = errno; // Use standard errno for send errors
        set_ft_errno(static_cast<FT_Error>(errno)); // Optionally map errno to FT_Error if needed
    } else {
        _error = static_cast<int>(FT_Error::NONE);
    }

    return bytes_sent;
}

// Receive data
ssize_t ft_socket::receive_data(void *buffer, size_t size, int flags) {
    if (sock_fd < 0) {
        _error = static_cast<int>(FT_Error::SOCKET_CREATION_FAILED);
        set_ft_errno(static_cast<FT_Error>(FT_Error::SOCKET_CREATION_FAILED));
        return -1;
    }

    ssize_t bytes_received = recv(sock_fd, buffer, size, flags);
    if (bytes_received < 0) {
        _error = errno; // Use standard errno for recv errors
        set_ft_errno(static_cast<FT_Error>(errno)); // Optionally map errno to FT_Error if needed
    } else {
        _error = static_cast<int>(FT_Error::NONE);
    }

    return bytes_received;
}

// Close socket
bool ft_socket::close_socket() {
    if (sock_fd >= 0) {
        if (close(sock_fd) == 0) {
            sock_fd = -1;
            _error = static_cast<int>(FT_Error::NONE);
            return true;
        } else {
            _error = errno; // Use standard errno for close errors
            set_ft_errno(static_cast<FT_Error>(errno));
            return false;
        }
    }
    _error = static_cast<int>(FT_Error::NONE);
    return true;
}

// Get local error code
int ft_socket::get_error() const {
    return _error;
}

// Get error message
const char* ft_socket::get_error_message() const {
    return ft_strerror(_error);
}
