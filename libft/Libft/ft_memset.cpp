#include "libft.hpp"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	const char	*s;

	if (dst == nullptr && src == nullptr)
		return (nullptr);

	d = (char *)dst;
	s = (const char *)src;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
