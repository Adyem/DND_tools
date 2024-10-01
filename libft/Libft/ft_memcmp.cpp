#include <unistd.h>

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	const unsigned char	*string1;
	const unsigned char	*string2;
	size_t				i;

	i = 0;
	string1 = (const unsigned char *)pointer1;
	string2 = (const unsigned char *)pointer2;
	while (i < size)
	{
		if (string1[i] != string2[i])
			return (string1[i] - string2[i]);
		i++;
	}
	return (0);
}
