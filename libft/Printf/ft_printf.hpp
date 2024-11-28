#ifndef FT_PRINTF_HPP
#define FT_PRINTF_HPP

#include <stdarg.h>
#include <stddef.h>

int pf_printf(const char *format, ...) __attribute__((format(printf, 1, 2), hot));
int pf_printf_fd(int fd, const char *format, ...) __attribute__((format(printf, 2, 3), hot));

//Helper function don't call directly unless trough a printf like function
int pf_printf_fd_v(int fd, const char *format, va_list args);

#endif
