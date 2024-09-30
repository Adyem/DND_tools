#include "libft.hpp"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s; // Cast s to char* for pointer arithmetic

	i = 0;
	while (i < n)
	{
		ptr[i] = 0; // Use the casted pointer directly
		i++;
	}
}
