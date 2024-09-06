#include "dnd_tools.hpp"
#include "libft/libft/libft.hpp"

char **ft_resize_double_char(char **double_string, const char *string, int size)
{
    char **return_v;
    int i;
	int	j;

    if (!double_string)
        return (NULL);
    i = 0;
	while (double_string[i])
		i++;
	return_v = (char **)ft_calloc(i + size + 1, sizeof(char *));
	if (!return_v)
		return (NULL);
	j = 0;
    while (j < i)
	{
        return_v[j] = double_string[j];
		j++;
	}
    return_v[i] = ft_strdup(string);
    if (!return_v[i])
	{
        free(return_v);
        return (NULL);
    }
	j = i + 1;
    while (j < i + size + 1)
	{
        return_v[j] = NULL;
		j++;
	}
	return (return_v);
}
