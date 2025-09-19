#include "dnd_tools.hpp"
#include "libft/Errno/errno.hpp"
#include <fcntl.h>
#include <unistd.h>

int ft_is_caster_name_present(ft_set<ft_string> *caster_name_list, const char *name)
{
    const ft_string    *existing_name;
    ft_string           search_value(name);

    if (!caster_name_list || !name)
        return (0);
    if (search_value.get_error())
        return (0);
    existing_name = caster_name_list->find(search_value);
    if (existing_name)
        return (1);
    if (caster_name_list->get_error() != SET_NOT_FOUND
        && caster_name_list->get_error() != ER_SUCCESS)
        return (1);
    return (0);
}
