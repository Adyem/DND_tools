#include "ft_printf.hpp"
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

static size_t ft_strlen_printf(const char *s)
{
    size_t len = 0;
    if (!s)
        return (6);
    while (s[len])
        len++;
    return (len);
}

static void ft_putchar_fd(const char c, int fd, size_t *count)
{
    write(fd, &c, 1);
    (*count)++;
    return ;
}

static void ft_putstr_fd(const char *s, int fd, size_t *count)
{
    if (!s) {
        write(fd, "(null)", 6);
        *count += 6;
        return ;
    }
    size_t len = ft_strlen_printf(s);
    write(fd, s, len);
    *count += len;
    return ;
}

static void ft_putnbr_fd_recursive(long n, int fd, size_t *count)
{
    char c;
    if (n < 0) {
        ft_putchar_fd('-', fd, count);
        n = -n;
    }
    if (n >= 10)
        ft_putnbr_fd_recursive(n / 10, fd, count);
    c = '0' + (n % 10);
    ft_putchar_fd(c, fd, count);
    return ;
}

static void ft_putnbr_fd(long n, int fd, size_t *count)
{
    ft_putnbr_fd_recursive(n, fd, count);
    return ;
}

static void ft_putunsigned_fd_recursive(unsigned long n, int fd, size_t *count)
{
    char c;
    if (n >= 10)
        ft_putunsigned_fd_recursive(n / 10, fd, count);
    c = '0' + (n % 10);
    ft_putchar_fd(c, fd, count);
    return ;
}

static void ft_putunsigned_fd(unsigned long n, int fd, size_t *count)
{
    ft_putunsigned_fd_recursive(n, fd, count);
    return ;
}

static void ft_puthex_fd_recursive(unsigned long n, int fd, bool uppercase, size_t *count)
{
    char c;
    if (n >= 16)
        ft_puthex_fd_recursive(n / 16, fd, uppercase, count);
    if ((n % 16) < 10)
        c = '0' + (n % 16);
    else
        c = (uppercase ? 'A' : 'a') + ((n % 16) - 10);
    ft_putchar_fd(c, fd, count);
    return ;
}

static void ft_puthex_fd(unsigned long n, int fd, bool uppercase, size_t *count)
{
    ft_puthex_fd_recursive(n, fd, uppercase, count);
    return ;
}

static void ft_putptr_fd(void *ptr, int fd, size_t *count)
{
    uintptr_t addr = (uintptr_t)ptr;
    ft_putstr_fd("0x", fd, count);
    ft_puthex_fd(addr, fd, false, count);
    return ;
}

static int ft_printf_fd_v(int fd, const char *format, va_list args)
{
    size_t count = 0;
    size_t i = 0;

    while (format[i])
	{
		if (format[i] == '%')
		{
            i++;
            if (format[i] == '\0')
                break;
            LengthModifier len_mod = LEN_NONE;
			if (format[i] == 'l')
			{
                len_mod = LEN_L;
                i++;
            }
			else if (format[i] == 'z')
			{
                len_mod = LEN_Z;
                i++;
            }
            char spec = format[i];
            if (spec == '\0')
                break;
			if (spec == 'c')
			{
                char c = (char)va_arg(args, int);
                ft_putchar_fd(c, fd, &count);
            }
			else if (spec == 's')
			{
                char *s = va_arg(args, char *);
                ft_putstr_fd(s, fd, &count);
            }
			else if (spec == 'd' || spec == 'i')
			{
				if (len_mod == LEN_L)
				{
                    long num = va_arg(args, long);
                    ft_putnbr_fd(num, fd, &count);
                }
				else
				{
                    int num = va_arg(args, int);
                    ft_putnbr_fd(num, fd, &count);
                }
            }
			else if (spec == 'u')
			{
				if (len_mod == LEN_L)
				{
                    unsigned long num = va_arg(args, unsigned long);
                    ft_putunsigned_fd(num, fd, &count);
                }
				else if (len_mod == LEN_Z)
				{
                    size_t num = va_arg(args, size_t);
                    ft_putunsigned_fd((unsigned long)num, fd, &count);
                }
				else
				{
                    unsigned int num = va_arg(args, unsigned int);
                    ft_putunsigned_fd(num, fd, &count);
                }
            }
			else if (spec == 'x' || spec == 'X')
			{
                bool uppercase = (spec == 'X');
				if (len_mod == LEN_L)
				{
                    unsigned long num = va_arg(args, unsigned long);
                    ft_puthex_fd(num, fd, uppercase, &count);
				}
				else if (len_mod == LEN_Z)
				{
                    size_t num = va_arg(args, size_t);
                    ft_puthex_fd((unsigned long)num, fd, uppercase, &count);
				}
				else
				{
                    unsigned int num = va_arg(args, unsigned int);
                    ft_puthex_fd(num, fd, uppercase, &count);
                }
            }
			else if (spec == 'p')
			{
                void *ptr = va_arg(args, void *);
                ft_putptr_fd(ptr, fd, &count);
            }
			else if (spec == 'b')
			{
                int b = va_arg(args, int);
                if (b)
                    ft_putstr_fd("true", fd, &count);
                else
                    ft_putstr_fd("false", fd, &count);
            }
			else if (spec == '%')
				ft_putchar_fd('%', fd, &count);
			else
			{
                ft_putchar_fd('%', fd, &count);
                ft_putchar_fd(spec, fd, &count);
            }
		}
		else
            ft_putchar_fd(format[i], fd, &count);
        i++;
    }
    return ((int)count);
}

int pf_printf_fd(int fd, const char *format, ...)
{
    va_list args;
    int printed_chars;

    if (!format)
        return (0);
    va_start(args, format);
    printed_chars = ft_printf_fd_v(fd, format, args);
    va_end(args);
    return (printed_chars);
}

int pf_printf(const char *format, ...)
{
    va_list args;
    int printed_chars;

    if (!format)
        return (0);
    va_start(args, format);
    printed_chars = ft_printf_fd_v(1, format, args);
    va_end(args);
    return (printed_chars);
}
