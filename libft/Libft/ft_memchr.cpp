#include "libft.hpp"

void	*ft_memchr(const void *pointer, int number, size_t size)
{
	size_t			i;
	unsigned char	*string;
	unsigned char	character;

	string = (unsigned char *)pointer;
	character = (unsigned char)number;
	i = 0;
	while (i < size)
	{
		if (*string == character)
			return (string);
		string++;
		i++;
	}
	return (nullptr);
}
