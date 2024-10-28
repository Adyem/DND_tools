#include "libft.hpp"
#include "../CPP_class/nullptr.hpp"

char	*ft_strchr(const char *s, int i)
{
	char	c;

	if (!s)
		return (ft_nullptr);
	c = (char)i;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (ft_nullptr);
}
