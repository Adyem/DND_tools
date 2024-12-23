#include "libft.hpp"
#include "../CPP_class/nullptr.hpp"

void	*ft_memchr(const void *pointer, int number, size_t size)
{
	size_t			index;
	unsigned char	*string;
	unsigned char	character;

	string = (unsigned char *)pointer;
	character = (unsigned char)number;
	index = 0;
	while (index < size)
	{
		if (*string == character)
			return (string);
		string++;
		index++;
	}
	return (ft_nullptr);
}
