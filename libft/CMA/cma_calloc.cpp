#include <stddef.h>
#include <stdbool.h>
#include "CMA.hpp"

void	*cma_calloc(int count, int size)
{
	void	*ptr;
	size_t	total_size;
	size_t	i;
	char	*char_ptr;

	if (count <= 0 || size <= 0)
		return (NULL);
	total_size = count * size;
	ptr = cma_malloc(total_size);
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
