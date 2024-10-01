#include "libft.hpp"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t	i;

	if (destination == nullptr || source == nullptr)
		return (nullptr);
	i = 0;
	while (i < size)
	{
		*(char *)((char *)destination + i) = *(char *)((const char *)source + i);
		i++;
	}
	return (destination);
}
