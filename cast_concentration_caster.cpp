#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/ft_printf.hpp"

int ft_update_caster_name(char ***caster_name, const char *input_name)
{
    char **temp;

    if (DEBUG == 1)
        ft_printf("adding the new caster name to the target struct %s\n", input_name);
    if (!(*caster_name))
    {
        *caster_name = (char **)ft_calloc(2, sizeof(char *));
        if (!(*caster_name))
        {
            ft_printf_fd(2, "165-Error allocating memory for caster name\n");
            return (1);
        }
        **caster_name = ft_strdup(input_name);
        if (!(**caster_name))
        {
            ft_printf_fd(2, "162-Error allocating memory for caster name\n");
            return (1);
        }
    }
    else
    {
        temp = ft_resize_double_char(*caster_name, input_name, 1);
        if (!temp)
        {
            ft_printf_fd(2, "298-Error allocating memory for caster name\n");
            return (1);
        }
        ft_free_double_char(*caster_name);
        *caster_name = temp;
    }
    return (0);
}
