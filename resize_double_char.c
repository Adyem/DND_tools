#include "dnd_tools.h"

char	**ft_resize_double_char(char **double_string, char *string, int size)
{
	char	**return_v;
	int		i;

	i = 0;
	while (double_string[i])
		i++;
	return_v = (char **)ft_calloc((i + size + 1), sizeof(char *));
	if (!return_v)
		return (NULL);
	i = 0;
	while (double_string[i])
	{
		return_v[i] = double_string[i];
		i++;
	}
	return_v[i] = ft_strdup(string);
	if (!double_string)
	{
		free(return_v);
		return (NULL);
	}
	return(return_v);
}
