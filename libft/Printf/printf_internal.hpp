#ifndef PRINTF_INTERNAL_HPP
# define PRINTF_INTERNAL_HPP

#include <cstdarg>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <stddef.h>

typedef enum
{
    LEN_NONE,
    LEN_L,
    LEN_Z
} LengthModifier;

size_t ft_strlen_printf(const char *s);
void ft_putchar_fd(const char c, int fd, size_t *count);
void ft_putstr_fd(const char *s, int fd, size_t *count);
void ft_putnbr_fd_recursive(long n, int fd, size_t *count);
void ft_putnbr_fd(long n, int fd, size_t *count);
void ft_putunsigned_fd_recursive(unsigned long n, int fd, size_t *count);
void ft_putunsigned_fd(unsigned long n, int fd, size_t *count);
void ft_puthex_fd_recursive(unsigned long n, int fd, bool uppercase, size_t *count);
void ft_puthex_fd(unsigned long n, int fd, bool uppercase, size_t *count);
void ft_putptr_fd(void *ptr, int fd, size_t *count);
int pf_printf_fd_v(int fd, const char *format, va_list args);

#endif
