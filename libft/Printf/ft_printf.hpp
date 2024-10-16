#ifndef FT_PRINTF_HPP
# define FT_PRINTF_HPP

# ifndef DEBUG
#  define DEBUG 0
# endif

int		ft_printf_fd(int fd, const char *format, ...);
int		ft_printf(const char *format, ...);

#endif
