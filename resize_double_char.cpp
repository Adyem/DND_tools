#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include <cstdlib>

char **ft_resize_double_char(char **double_string, const char *string, int size)
{
    if (!double_string)
        return (ft_nullptr);
    int current_count = 0;
    while (double_string[current_count])
        current_count++;
    char **resized_array = (char **)cma_calloc(current_count + size + 1, sizeof(char *));
    if (!resized_array)
        return (ft_nullptr);
    int index = 0;
    while (index < current_count)
    {
        resized_array[index] = cma_strdup(double_string[index]);
        if (!resized_array[index])
        {
            index--;
            while (index >= 0)
            {
                cma_free(resized_array[index]);
                index--;
            }
            cma_free(resized_array);
            return (ft_nullptr);
        }
        index++;
    }
    resized_array[current_count] = cma_strdup(string);
    if (!resized_array[current_count])
    {
        index = 0;
        while (index < current_count)
        {
            cma_free(resized_array[index]);
            index++;
        }
        cma_free(resized_array);
        return (ft_nullptr);
    }
    int additional_index = current_count + 1;
    while (additional_index < current_count + size + 1)
    {
        resized_array[additional_index] = ft_nullptr;
        additional_index++;
    }
    return (resized_array);
}
