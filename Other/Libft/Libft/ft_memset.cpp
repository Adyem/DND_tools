#include "libft.hpp"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	const char	*s;

	if (dst == nullptr && src == nullptr)
		return (nullptr);

	d = (char *)dst;       // Cast dst to char* once
	s = (const char *)src; // Cast src to const char* once

	i = 0;
	while (i < n)
	{
		d[i] = s[i]; // Now you can simply use d and s without casting inside the loop
		i++;
	}
	return (dst);
}
