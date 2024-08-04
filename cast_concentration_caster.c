#include "dnd_tools.h"

int ft_update_caster_name(char ***caster_name, const char *input_name, t_buff *buff)
{
    char	**temp;

	(void)buff;
	if (DEBUG == 1)
		ft_printf("adding the new caster name to the target struct\n");
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
        if (temp)
        {
			ft_free_double_char(*caster_name);
            *caster_name = temp;
        }
        else
        {
            ft_printf_fd(2, "297-Error allocating memory for caster name\n");
            return (1);
        }
    }
    return (0);
}
