#include "CMA.hpp"
#include "../Printf/ft_printf.hpp"

void	cma_free_double(char **content)
{
	int	i;

	i = 0;
	if (content)
	{
		while (content[i])
		{
			ft_printf("freeing %s\n", content[i]);
			cma_free(content[i]);
			i++;
		}
		cma_free(content);
	}
	return ;
}
