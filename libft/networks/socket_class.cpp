#include "socket_class.hpp"
#include "../CPP_class/nullptr.hpp"
#include "../Errno/errno.hpp"
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

ft_socket::ft_socket(const SocketConfig &config) {
    if (config.type == SocketType::SERVER) {
        setup_server(config.ip, config.port, config.backlog);
    }
    else if (config.type == SocketType::CLIENT) {
        setup_client(config.ip, config.port);
    }
    else {
        // Handle other types or set custom error
        ft_errno = FT_ERROR_UNSUPPORTED_SOCKET_TYPE;
        _error = ft_errno;
    }
}

ft_socket::~ft_socket() {
    if (sock_fd >= 0) {
        close(sock_fd);
    }
}

void ft_socket::setup_server(const std::string &ip, int port, int backlog) {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
        return;
    }
    
    int opt = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
        close(sock_fd);
        sock_fd = -1;
        return;
    }
    
    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0) {
        ft_errno = FT_ERROR_INVALID_CONFIGURATION;
        _error = ft_errno;
        close(sock_fd);
        sock_fd = -1;
        return;
    }

    if (::bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
        close(sock_fd);
        sock_fd = -1;
        return;
    }

    if (::listen(sock_fd, backlog) < 0) {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
        close(sock_fd);
        sock_fd = -1;
        return;
    }

    _error = ER_SUCCESS;
}

void ft_socket::setup_client(const std::string &ip, int port) {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
        return;
    }

    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
        ft_errno = FT_ERROR_INVALID_CONFIGURATION;
        _error = ft_errno;
        close(sock_fd);
        sock_fd = -1;
        return;
    }

    if (::connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
        close(sock_fd);
        sock_fd = -1;
        return;
    }

    // If everything succeeded, ensure _error is ER_SUCCESS
    _error = ER_SUCCESS;
}

// Send data
ssize_t ft_socket::send_data(const void *data, size_t size, int flags) {
    if (sock_fd < 0) {
        ft_errno = SOCKET_INVALID_CONFIGURATION; // Ensure this error code exists in PTErrorCode
        _error = ft_errno;
        return -1;
    }

    ssize_t bytes_sent = ::send(sock_fd, data, size, flags);
    if (bytes_sent < 0) {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
    }
    else {
        _error = ER_SUCCESS;
    }

    return bytes_sent;
}

// Receive data
ssize_t ft_socket::receive_data(void *buffer, size_t size, int flags) {
    if (sock_fd < 0) {
        ft_errno = FT_EINVAL;
        _error = ft_errno;
        return -1;
    }

    ssize_t bytes_received = ::recv(sock_fd, buffer, size, flags);
    if (bytes_received < 0) {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
    }
    else {
        _error = ER_SUCCESS;
    }

    return bytes_received;
}

// Close socket
bool ft_socket::close_socket() {
    if (sock_fd >= 0) {
        if (::close(sock_fd) == 0) {
            sock_fd = -1;
            _error = ER_SUCCESS;
            return true;
        }
        else {
            ft_errno = errno + ERRNO_OFFSET;
            _error = ft_errno;
            return false;
        }
    }
    _error = ER_SUCCESS;
    return true;
}

// Accept a new connection (for server sockets)
std::unique_ptr<ft_socket> ft_socket::accept_connection() {
    sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_fd = ::accept(sock_fd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd < 0) {
        ft_errno = errno + ERRNO_OFFSET;
        _error = ft_errno;
        return ft_nullptr;
    }

    // Create a new ft_socket instance for the client
    SocketConfig client_config{
        SocketType::RAW, // Assuming RAW for client sockets
        "",               // IP not needed for client socket creation
        0,                // Port not needed
        0                 // Backlog not used
    };

    // Instantiate a new ft_socket and set its sock_fd directly
    auto client_socket = std::make_unique<ft_socket>(client_config);
    client_socket->sock_fd = client_fd;
    client_socket->_error = ER_SUCCESS;

    return client_socket;
}

// Get local error code
int ft_socket::get_error() const {
    return _error;
}

// Get error message
const char* ft_socket::get_error_message() const {
    return ft_strerror(_error);
}
