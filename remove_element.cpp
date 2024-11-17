#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include <fcntl.h>
#include <unistd.h>

void	ft_remove_element(char **array, char *element, bool free_element)
{
	int	i;
	int	j;

	if (!array || !element)
		return ;
	i = 0;
	while (array[i] && array[i] != element)
		i++;
	if (array[i] == element)
	{
		if (free_element)
			cma_free(element);
		j = i;
		while (array[j])
		{
			array[j] = array[j + 1];
			j++;
		}
	}
	return ;
}
