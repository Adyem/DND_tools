#include "dnd_tools.h"

void	ft_chaos_goblin_turn(t_char *info)
{
	ft_update_buf(info);
	ft_printf("The chaos_goblin will try to make either a ranged or melee attack during his turn\n");
	ft_printf("Chaos_goblin currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
}

t_char	*ft_chaos_goblin(int index, const char **input, t_name *name, int exception)
{
	int		error;
	t_char	*info;

	info = (t_char *)calloc(1, sizeof(t_char));
	if (!info)
		return (NULL);
	*info = CHAOS_GOBLIN_INFO;
	info->name = input[0];
	info->struct_name = name;
	info->save_file = ft_strjoin("data/", input[0]);
	if (!info->save_file)
		return (NULL);
	error = ft_npc_open_file(info);
	if (error)
		return (NULL);
	error = ft_npc_check_info(info);
	if (error)
		return (NULL);
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (NULL);
}
