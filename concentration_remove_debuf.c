#include "dnd_tools.h"

void	ft_concentration_remove_hunters_mark(t_char *info, t_char *target)
{
	int	i;
	int	j;

	i = 0;
	if (target->version_number < 2)
	{
		ft_printf_fd(2, "260-Error Hunters_mark not supported for target %s\n", target->name);
		return ;
	}
	while (target->debufs.hunters_mark.caster_name && target->debufs.hunters_mark.caster_name[i])
	{
		if (ft_strcmp_dnd(target->debufs.hunters_mark.caster_name[i], info->name) == 0)
		{
			free(target->debufs.hunters_mark.caster_name[i]);
			j = i;
			while (target->debufs.hunters_mark.caster_name[j])
			{
				target->debufs.hunters_mark.caster_name[j] = target->debufs.hunters_mark.caster_name[j + 1];
				j++;
			}
			target->debufs.hunters_mark.amount--;
			if (j > 0)
				target->debufs.hunters_mark.caster_name[j - 1] = NULL;
			return ;
		}
		i++;
	}
	ft_printf_fd(2, "304-Error: %s Hunters mark debuff not found\n", target->name);
	return ;
}

