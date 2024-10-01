#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include <cstdlib>

char **ft_resize_double_char(char **double_string, const char *string, int size)
{
    char **return_v;
    int i;
	int	j;

    if (!double_string)
        return (nullptr);
    i = 0;
	while (double_string[i])
		i++;
	return_v = (char **)ft_calloc(i + size + 1, sizeof(char *));
	if (!return_v)
		return (nullptr);
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
        return (nullptr);
    }
	j = i + 1;
    while (j < i + size + 1)
	{
        return_v[j] = nullptr;
		j++;
	}
	return (return_v);
}
