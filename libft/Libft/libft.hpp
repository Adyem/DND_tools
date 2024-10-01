#ifndef LIBFT_HPP
# define LIBFT_HPP

#include <cstddef>

int		ft_strlen(const char *string);
char	*ft_strchr(const char *s, int i);
int		ft_atoi(const char *str);
void	ft_bzero(void *string, size_t size);
void	*ft_memchr(const void *pointer, int character, size_t size);
void	*ft_memcpy(void *destination, const void *source, size_t size);
int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
char	**ft_split(char const *s, char c);
void	*ft_memmove(void *destination, const void *source, size_t size);
char	*ft_strchr(const char *s, int i);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *string_1, char const *string_2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
long		ft_atol(const char *str);
int		ft_isdigit(int c);
char	*ft_itoa(int n);

#endif
