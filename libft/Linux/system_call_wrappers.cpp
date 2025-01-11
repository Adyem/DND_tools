#if defined(__linux__) || defined(__APPLE__)

#include <fcntl.h>
#include <unistd.h>
#include "linux_file.hpp"

int ft_open(const char *pathname, int flags, mode_t mode)
{
    int fd = open(pathname, flags, mode);
    if (fd == -1)
        return (-1);
    return (fd);
}

ssize_t ft_write(int fd, const void *buf, size_t count)
{
    ssize_t written = write(fd, buf, count);
    if (written == -1)
        return (-1);
    return (written);
}

ssize_t ft_read(int fd, void *buf, size_t count)
{
    ssize_t bytes_read = read(fd, buf, count);
    if (bytes_read == -1)
        return (-1);
    return (bytes_read);
}

int ft_close(int fd)
{
    if (close(fd) == -1)
        return (-1);
    return (0);
}

#endif
