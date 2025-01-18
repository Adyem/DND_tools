#ifndef FILE_H
# define FILE_H

# include "../Windows/windows_file.hpp"

# if defined(__linux__) || defined(__APPLE__)

# include <fcntl.h>
# include <unistd.h>

void	ft_initialize_standard_file_descriptors();
int 	ft_write(int file_descriptor, char *data, int bytes);
ssize_t ft_read(int fd, void *buf, size_t count);
int		ft_close(int fd);
int		ft_open(const char* pathname);
int 	ft_open(const char* pathname, int flags);
int 	ft_open(const char* pathname, int flags, mode_t mode);

static inline void use_dummy(void)
{
    ft_dummy();
}

# endif

#endif
