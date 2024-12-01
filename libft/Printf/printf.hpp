#ifndef PRINTF_HPP
#define PRINTF_HPP

#include <stdarg.h>
#include <stddef.h>

int pf_printf(const char *format, ...) __attribute__((format(printf, 1, 2), hot));
int pf_printf_fd(int fd, const char *format, ...) __attribute__((format(printf, 2, 3), hot));

#endif
