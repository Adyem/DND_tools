#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 

int nw_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    if (bind(sockfd, addr, addrlen) == -1)
        return (-1);
    return (0);
}

int nw_listen(int sockfd, int backlog)
{
    if (listen(sockfd, backlog) == -1)
        return (-1);
    return (0);
}

int nw_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int new_fd = accept(sockfd, addr, addrlen);
    if (new_fd == -1)
        return (-1);
    return (new_fd);
}

int nw_socket(int domain, int type, int protocol)
{
    int sockfd = socket(domain, type, protocol);
    if (sockfd == -1)
        return (-1);
    return (sockfd);
}
