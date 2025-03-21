#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>

int ft_double_char_length(const char **double_char)
{
    if (!double_char)
        return (0);
    int index = 0;
    while (double_char[index])
        index++;
    return (index);
}

int ft_is_caster_name_present(char **caster_name_list, const char *name)
{
    if (!caster_name_list || !name)
        return (0);
    int index = 0;
    while (caster_name_list[index])
    {
        if (ft_strcmp_dnd(caster_name_list[index], name) == 0)
            return (1);
        index++;
    }
    return (0);
}
