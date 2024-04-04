#include "dnd_tools.h"

void	ft_air_totem(int index, char **input)
{
	t_char	*info;

	info = (t_char *)malloc(sizeof(t_char));
	if (!info)
		return ;
	*info = AIR_TOTEM_INFO;
	ft_npc_change_stats(info, index, input);
	free(info);
	return ;
}
