#include "dnd_tools.h"

void	ft_free_info(t_char *info)
{
	if (DEBUG == 1)
		ft_printf("freeing info %s\n", info->name);
	if (info->version_number >= 2)
	{
		ft_free_double_char(info->debufs.hunters_mark.caster_name);
		ft_free_double_char(info->concentration.targets);
	}
	if (info->free_save == 1 || info->version_number >= 2)
		free(info->save_file);
	free(info);
	return ;
}
