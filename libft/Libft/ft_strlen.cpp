#include <stddef.h>

int ft_strlen(const char *string)
{
	int	index;

	if (!string)
		return (0);
	index = 0;
	while (string[index])
		index++;
	return (index);
}
