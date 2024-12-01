#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"

int ft_update_caster_name(char ***caster_name, const char *input_name)
{
    char **temp;

    if (DEBUG == 1)
        pf_printf("adding the new caster name to the target struct %s\n", input_name);
    if (!(*caster_name))
    {
        *caster_name = (char **)cma_calloc(2, sizeof(char *), false);
        if (!(*caster_name))
        {
            pf_printf_fd(2, "165-Error allocating memory for caster name\n");
            return (1);
        }
        **caster_name = cma_strdup(input_name, false);
        if (!(**caster_name))
        {
            pf_printf_fd(2, "162-Error allocating memory for caster name\n");
            return (1);
        }
    }
    else
    {
        temp = ft_resize_double_char(*caster_name, input_name, 1);
        if (!temp)
        {
            pf_printf_fd(2, "298-Error allocating memory for caster name\n");
            return (1);
        }
        cma_free_double(*caster_name);
        *caster_name = temp;
    }
    return (0);
}
