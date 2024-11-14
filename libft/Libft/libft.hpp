#ifndef LIBFT_HPP
# define LIBFT_HPP

#define SUCCES 0
#define FAILURE 1

#include <cstddef>

int		ft_strlen(const char *string);
char	*ft_strchr(const char *s, int i);
int		ft_atoi(const char *str);
void	ft_bzero(void *string, size_t size);
void	*ft_memchr(const void *pointer, int character, size_t size);
void	*ft_memcpy(void *destination, const void *source, size_t size);
int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
void	*ft_memmove(void *destination, const void *source, size_t size);
char	*ft_strchr(const char *s, int i);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
long	ft_atol(const char *str);
int		ft_strcmp(const char *string1, const char *string2);

#endif
