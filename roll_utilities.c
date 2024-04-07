#include "dnd_tools.h"

void	ft_free_parse(char **to_parse)
{
	int	i;

	i = 0;
	if (to_parse)
	{
		while (to_parse[i])
		{
			free(to_parse[1]);
			i++;
		}
		free(to_parse);
	}
}
