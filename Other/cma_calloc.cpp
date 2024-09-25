#include <stddef.h>
#include <stdbool.h>

void	*ft_calloc(int count, int size, bool criticality)
{
	void	*ptr;
	size_t	total_size;
	size_t	i;
	char	*char_ptr;

	if (count <= 0 || size <= 0)
		return (NULL);
	total_size = count * size;
	ptr = cma_malloc(total_size, criticality);
	if (!ptr)
		return (NULL);
	char_ptr = (char *)ptr;
	i = 0;
	while (i < total_size)
	{
		char_ptr[i] = 0;
		i++;
	}
	return (ptr);
}
