#include "libft.hpp"

void	*ft_memchr(const void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	character;

	str = (unsigned char *)b;
	character = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*str == character)
			return (str);
		str++;
		i++;
	}
	return (nullptr);
}
