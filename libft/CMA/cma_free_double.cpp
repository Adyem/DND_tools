#include "CMA.hpp"

void	cma_free_double(char **content)
{
	int	i;

	i = 0;
	if (content)
	{
		while (content[i])
		{
			cma_free(content[i]);
			i++;
		}
		cma_free(content);
	}
	return ;
}
