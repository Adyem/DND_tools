#ifndef FT_PRINTF_HPP
#define FT_PRINTF_HPP

#include <stdarg.h>
#include <stddef.h>

int ft_printf(const char *format, ...) __attribute__((format(printf, 1, 2), hot));
int ft_printf_fd(int fd, const char *format, ...) __attribute__((format(printf, 2, 3), hot));

#endif
