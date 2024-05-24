#include "dnd_tools.h"

char **ft_set_stats_strings(t_char *info, char **content, int index, int ofset, char **data)
{
	int	i;

	if (!data)
	{
		data = (char **)malloc(sizeof(char *) * 2);
		if (!data)
			return (NULL);
		data[0] = (char *)malloc((ft_strlen(content[index]) + 1) * sizeof(char));
		if (!data[0])
		{
			ft_free_content(data);
			return (NULL);
		}
		i = 0;
		while (content[index][i + ofset])
		{
			data[0][i] = content[index][i + ofset];
			i++;
		}
		data[1] == NULL;
	}
}
