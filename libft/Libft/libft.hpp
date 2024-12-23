#ifndef LIBFT_HPP
# define LIBFT_HPP

#define SUCCES 0
#define FAILURE 1

#include <cstddef>

int		ft_strlen(const char *string);
char	*ft_strchr(const char *string, int char_to_find);
int		ft_atoi(const char *string);
void	ft_bzero(void *string, size_t size);
void	*ft_memchr(const void *pointer, int character, size_t size);
void	*ft_memcpy(void *destination, const void *source, size_t size);
int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
void	*ft_memmove(void *destination, const void *source, size_t size);
char	*ft_strchr(const char *string, int char_to_find);
size_t	ft_strlcat(char *destination, const char *source, size_t bufferSize);
size_t	ft_strlcpy(char *destination, const char *source, size_t bufferSize);
int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
char	*ft_strrchr(const char *string, int char_to_find);
char	*ft_strnstr(const char *haystack, const char *needle, size_t length);
int		ft_strncmp(const char *string_1, const char *string_2, size_t max_len);
int		ft_isdigit(int character);
long	ft_atol(const char *string);
int		ft_strcmp(const char *string1, const char *string2);

#endif
