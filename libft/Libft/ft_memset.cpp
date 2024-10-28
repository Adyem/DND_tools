#include "libft.hpp"
#include "../CPP_class/nullptr.hpp"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	const char	*s;

	if (dst == ft_nullptr && src == ft_nullptr)
		return (ft_nullptr);

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
