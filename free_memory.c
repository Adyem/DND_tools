#include "dnd_tools.h"

void	ft_free_content(char **content)
{
	int	i;

	i = 0;
	if (content)
	{
		while (content[i])
		{
			free(content[i]);
			i++;
		}
		free(content);
	}
	return ;
}
