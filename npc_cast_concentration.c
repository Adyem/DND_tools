#include "dnd_tools.h"

void	ft_cast_hunters_mark(t_char *info, char **input)
{
	t_char	*target;

	if (ft_set_stats_check_name(input[2]))
		return (ft_printf_fd(2, "Error target does not exist"), (void)0);
	target = ft_get_info(input[2], info->struct_name);
	if (!target)
		return (ft_printf_fd(2, "295-Error getting info %s\n", input[2]), (void)0);
}
