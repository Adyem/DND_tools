#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include <cstdlib>

char **ft_resize_double_char(char **double_string, const char *string, int size)
{
    if (!double_string)
        return (nullptr);
    int i = 0;
    while (double_string[i])
        i++;
    char **return_v = (char **)cma_calloc(i + size + 1, sizeof(char *), false);
    if (!return_v)
        return (nullptr);
    int j = 0;
    while (j < i)
    {
        return_v[j] = cma_strdup(double_string[j], false);
        if (!return_v[j])
        {
            j--;
            while (j >= 0)
            {
                cma_free(return_v[j]);
                j--;
            }
            cma_free(return_v);
            return (nullptr);
        }
        j++;
    }
    return_v[i] = cma_strdup(string, false);
    if (!return_v[i])
    {
        j = 0;
        while (j < i)
        {
            cma_free(return_v[j]);
            j++;
        }
        cma_free(return_v);
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
