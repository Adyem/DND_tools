#include "libft.hpp"
#include "../CPP_class/nullptr.hpp"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t	i;

	if (destination == ft_nullptr || source == ft_nullptr)
		return (ft_nullptr);
	i = 0;
	while (i < size)
	{
		*(char *)((char *)destination + i) = *(char *)((const char *)source + i);
		i++;
	}
	return (destination);
}
