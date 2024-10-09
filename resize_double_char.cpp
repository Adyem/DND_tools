#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include <cstdlib>

char **ft_resize_double_char(char **double_string, const char *string, int size)
{
    if (!double_string)
        return (nullptr);
    int i = 0;
    while (double_string[i])
        i++;
    char **return_v = (char **)ft_calloc(i + size + 1, sizeof(char *));
    if (!return_v)
        return (nullptr);
    int j = 0;
    while (j < i)
    {
        return_v[j] = ft_strdup(double_string[j]);
        if (!return_v[j])
        {
            j--;
            while (j >= 0)
            {
                free(return_v[j]);
                j--;
            }
            free(return_v);
            return (nullptr);
        }
        j++;
    }
    return_v[i] = ft_strdup(string);
    if (!return_v[i])
    {
        j = 0;
        while (j < i)
        {
            free(return_v[j]);
            j++;
        }
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
