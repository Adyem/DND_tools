#ifndef MYFILE_H
# define MYFILE_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# ifdef _WIN32
#  define O_RDONLY    0x0000
#  define O_WRONLY    0x0001
#  define O_RDWR      0x0002
#  define O_CREAT     0x0100
#  define O_EXCL      0x0200
#  define O_TRUNC     0x0400
#  define O_APPEND    0x0800

# else
#  include <fcntl.h>
# endif

# ifdef __cplusplus
extern "C"
{
# endif

int ft_open(const char *pathname, int flags, int mode); 
int ft_read(int fd, void *buf, unsigned int count);
int ft_write(int fd, const void *buf, unsigned int count);
int ft_close(int fd);

# ifdef __cplusplus
}
# endif

#endif
