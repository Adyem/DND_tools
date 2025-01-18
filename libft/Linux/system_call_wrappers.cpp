#if defined(__linux__) || defined(__APPLE__)

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

int ft_open(const char* pathname)
{
    int fd = open(pathname, O_RDONLY);
    if (fd == -1)
        return (-1);
    return (fd);
}

int ft_open(const char* pathname, int flags)
{
    int fd = open(pathname, flags);
    if (fd == -1)
        return (-1);
    return (fd);
}

int ft_open(const char* pathname, int flags, mode_t mode)
{
    int fd = open(pathname, flags, mode);
    if (fd == -1)
        return (-1);
    return (fd);
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

int ft_write(int file_descriptor, char *data, int bytes)
{
    if (write(file_descriptor, data, bytes) == -1)
        return (-1);
    return (0);
}

#endif
