#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/CPP_class/class_nullptr.hpp"

t_char *ft_get_info(const char *tf_name, t_name *name)
{
    t_name        *temp = name;
    t_char        *info = ft_nullptr;
    int            found = 0;
    const char    *input[2] = {tf_name, ft_nullptr};
    while (temp != ft_nullptr && !found)
    {
        if (ft_strcmp_dnd(tf_name, temp->name) == 0)
        {
            info = temp->function(0, input, name, 1);
            found = 1;
        }
        temp = temp->next;
    }
    return (info);
}
