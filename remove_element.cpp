#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>

void	ft_remove_element(const char **array, const char *element)
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
		j = i;
		while (array[j])
		{
			array[j] = array[j + 1];
			j++;
		}
	}
	return ;
}
