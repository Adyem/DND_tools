#ifndef FILE_H
# define FILE_H

# include "../windows/file.hpp"

# if defined(__linux__) || defined(__APPLE__)

# include <fcntl.h>
# include <unistd.h>

int 	ft_open(const char *pathname, int flags, mode_t mode);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
int		ft_close(int fd);

static inline void use_dummy(void)
{
    ft_dummy();
}

# endif

#endif
