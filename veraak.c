#include "dnd_tools.h"

void	ft_veraak_turn(t_char *info)
{
	ft_update_buf(info);
	ft_printf("The veraak will try to make either a ranged or melee attack during his turn\n");
	ft_printf("Veraak currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
}

t_char	*ft_veraak(int index, char **input, t_name *name, int exception)
{
	t_char	*info;

	info = (t_char *)calloc(1, sizeof(t_char));
	if (!info)
		return (NULL);
	*info = VERAAK_INFO;
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