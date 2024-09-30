#include "libft.hpp"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == nullptr && src == nullptr)
		return (nullptr);
	i = 0;
	while (i < n)
	{
		*(char *)((char *)dst + i) = *(char *)((const char *)src + i); // Explicit cast to char*
		i++;
	}
	return (dst);
}
