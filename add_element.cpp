#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void ft_add_element(const char ***array, const char *element)
{
    size_t i, current_size;
    const char **new_array;

    if (!array || !element)
        return ;
    if (*array == NULL)
    {
        new_array = static_cast<const char **>(cma_malloc(2 * sizeof(char *)));
        if (!new_array)
            return ;
        new_array[0] = element;
        new_array[1] = NULL;
        *array = new_array;
        return ;
    }
    i = 0;
    while ((*array)[i] != NULL)
    {
        if (strcmp((*array)[i], element) == 0)
            return ;
        i++;
    }
    current_size = (i + 2) * sizeof(char *);
    new_array = static_cast<const char **>(cma_realloc(*array, current_size));
    if (!new_array)
        return ;
    new_array[i] = element;
    new_array[i + 1] = NULL;
    *array = new_array;
}
