#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

// Calculate the length of a string
static size_t ft_strlen(const char *s) {
    size_t len = 0;
    if (!s)
        return 6; // Length of "(null)"
    while (s[len])
        len++;
    return len;
}

// Write a single character and update count
static void ft_putchar_fd(char c, int fd, size_t *count) {
    write(fd, &c, 1);
    (*count)++;
}

// Write a string and update count
static void ft_putstr_fd(char *s, int fd, size_t *count) {
    if (!s) {
        write(fd, "(null)", 6);
        *count += 6;
        return;
    }
    size_t len = ft_strlen(s);
    write(fd, s, len);
    *count += len;
}

// Recursively write a signed number
static void ft_putnbr_fd_recursive(long n, int fd, size_t *count) {
    char c;
    if (n < 0) {
        ft_putchar_fd('-', fd, count);
        n = -n;
    }
    if (n >= 10)
        ft_putnbr_fd_recursive(n / 10, fd, count);
    c = '0' + (n % 10);
    ft_putchar_fd(c, fd, count);
}

// Write a signed integer
static void ft_putnbr_fd(int n, int fd, size_t *count) {
    ft_putnbr_fd_recursive((long)n, fd, count);
}

// Recursively write an unsigned number
static void ft_putunsigned_fd_recursive(unsigned long n, int fd, size_t *count) {
    char c;
    if (n >= 10)
        ft_putunsigned_fd_recursive(n / 10, fd, count);
    c = '0' + (n % 10);
    ft_putchar_fd(c, fd, count);
}

// Write an unsigned integer
static void ft_putunsigned_fd(unsigned int n, int fd, size_t *count) {
    ft_putunsigned_fd_recursive((unsigned long)n, fd, count);
}

// Recursively write a hexadecimal number
static void ft_puthex_fd_recursive(unsigned long n, int fd, bool uppercase, size_t *count) {
    char c;
    if (n >= 16)
        ft_puthex_fd_recursive(n / 16, fd, uppercase, count);
    if ((n % 16) < 10)
        c = '0' + (n % 16);
    else
        c = (uppercase ? 'A' : 'a') + ((n % 16) - 10);
    ft_putchar_fd(c, fd, count);
}

// Write a hexadecimal number
static void ft_puthex_fd(unsigned long n, int fd, bool uppercase, size_t *count) {
    ft_puthex_fd_recursive(n, fd, uppercase, count);
}

// Write a pointer address
static void ft_putptr_fd(void *ptr, int fd, size_t *count) {
    uintptr_t addr = (uintptr_t)ptr;
    ft_putstr_fd("0x", fd, count);
    ft_puthex_fd(addr, fd, false, count);
}

// Helper function to handle variadic arguments with va_list
static int ft_printf_fd_v(int fd, const char *format, va_list args) {
    size_t count = 0;
    size_t i = 0;
    while (format[i]) {
        if (format[i] == '%') {
            i++;
            if (format[i] == '\0')
                break;
            if (format[i] == 'c') {
                char c = (char)va_arg(args, int);
                ft_putchar_fd(c, fd, &count);
            }
            else if (format[i] == 's') {
                char *s = va_arg(args, char *);
                ft_putstr_fd(s, fd, &count);
            }
            else if (format[i] == 'd' || format[i] == 'i') {
                int num = va_arg(args, int);
                ft_putnbr_fd(num, fd, &count);
            }
            else if (format[i] == 'u') {
                unsigned int num = va_arg(args, unsigned int);
                ft_putunsigned_fd(num, fd, &count);
            }
            else if (format[i] == 'x') {
                unsigned int num = va_arg(args, unsigned int);
                ft_puthex_fd(num, fd, false, &count);
            }
            else if (format[i] == 'X') {
                unsigned int num = va_arg(args, unsigned int);
                ft_puthex_fd(num, fd, true, &count);
            }
            else if (format[i] == 'p') {
                void *ptr = va_arg(args, void *);
                ft_putptr_fd(ptr, fd, &count);
            }
            else if (format[i] == 'b') {
                int b = va_arg(args, int);
                if (b)
                    ft_putstr_fd("true", fd, &count);
                else
                    ft_putstr_fd("false", fd, &count);
            }
            else if (format[i] == '%') {
                ft_putchar_fd('%', fd, &count);
            }
            else {
                ft_putchar_fd('%', fd, &count);
                ft_putchar_fd(format[i], fd, &count);
            }
        }
        else {
            ft_putchar_fd(format[i], fd, &count);
        }
        i++;
    }
    return (int)count;
}

// ft_printf_fd function that handles variadic arguments
int ft_printf_fd(int fd, const char *format, ...) {
    va_list args;
    int printed_chars;

    if (!format)
        return -1;

    va_start(args, format);
    printed_chars = ft_printf_fd_v(fd, format, args);
    va_end(args);
    return printed_chars;
}

// ft_printf function that writes to standard output (fd = 1)
int ft_printf(const char *format, ...) {
    va_list args;
    int printed_chars;

    if (!format)
        return -1;

    va_start(args, format);
    printed_chars = ft_printf_fd_v(1, format, args);
    va_end(args);
    return printed_chars;
}
