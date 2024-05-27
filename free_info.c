#include "dnd_tools.h"

void	ft_free_info(t_char *info)
{
	ft_free_content(info->concentration.targets);
	if (info->free_save == 1)
		free(info->save_file);
	free(info);
	return ;
}
