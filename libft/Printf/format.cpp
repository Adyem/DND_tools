#include "printf_internal.hpp"
#include <cstdarg>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <stddef.h>

int pf_printf_fd_v(int fd, const char *format, va_list args)
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
