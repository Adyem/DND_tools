#include "dnd_tools.h"

char **ft_set_stats_strings(char **content, int index, int ofset, char **data)
{
	char	**temp;
	int		i;

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
		data[0] = ft_strdup(&content[index][ofset]);
		data[1] = NULL;
	}
	else if (data)
	{
		i = 0;
		while (data[i])
			i++;
		temp = (char **)malloc((i + 2) * sizeof(char *));
		if (!temp)
		{
			ft_free_content(data);
			return (NULL);
		}
		i = 0;
		while (data[i])
		{
			temp[i] = data[i];
			i++;
		}
		free(data);
		data = temp;
		data[i] = ft_strdup(&content[index][ofset]);
		if (!data[i])
		{
			ft_free_content(data);
			return (NULL);
		}
		data[i + 1] = NULL;
	}
	return (data);
}
