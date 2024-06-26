#include "dnd_tools.h"

void	ft_goblin_turn(t_char *info)
{
	ft_update_buf(info);
	ft_printf("The goblin will try to make either a ranged or melee attack during his turn\n");
	ft_printf("Goblin currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
	if (info->stats.health < info->dstats.health / 2)
		ft_printf("the goblin is on low health and can disengage as a bonus action\n");
}

t_char	*ft_goblin(int index, char **input, t_name *name, int exception)
{
	t_char	*info;

	info = (t_char *)calloc(1, sizeof(t_char));
	if (!info)
		return (NULL);
	*info = GOBLIN_INFO;
	info->name = input[0];
	info->struct_name = name;
	info->save_file = ft_strjoin("data/", input[0]);
	if (!info->save_file)
		return (NULL);
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (NULL);
}
