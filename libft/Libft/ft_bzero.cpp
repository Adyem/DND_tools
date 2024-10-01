#include "libft.hpp"

void	ft_bzero(void *pointer, size_t size)
{
	size_t	i;
	char	*string;

	string = (char *)pointer;
	i = 0;
	while (i < size)
	{
		string[i] = 0;
		i++;
	}
}
