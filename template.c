#include "dnd_tools.h"

void	ft_template_turn(t_char *info)
{
	ft_update_buf(info);
	if (info->flags.prone)
	{
		ft_printf("%s will use his/her action to stand up\n", info->name);
		info->flags.prone = 0;
	}
	else
		ft_printf("The template will try to make either a ranged or melee attack during his turn\n");
	ft_printf("Template currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
}

t_char	*ft_template(const int index, const char **input, t_name *name, int exception)
{
	int		error;
	t_char	*info;

	if (DEBUG == 1)
		ft_printf("exception = %i\n", exception);
	info = (t_char *)calloc(1, sizeof(t_char));
	if (!info)
		return (NULL);
	*info = TEMPLATE_INFO;
	info->name = input[0];
	info->struct_name = name;
	info->save_file = ft_strjoin("data/", input[0]);
	if (!info->save_file)
	{
		ft_free_info(info);
		return (NULL);
	}
	if (index == 2)
	{
		if (ft_strcmp_dnd(input[1], "init") == 0)
		{
			ft_npc_write_file(info, &info->dstats, &info->d_resistance, -1);
			ft_printf("Stats for %s written on a file\n", info->name);
			ft_free_info(info);
			return (NULL);
		}
	}
	error = ft_npc_open_file(info);
	if (error)
	{
		ft_free_info(info);
		return (NULL);
	}
	error = ft_npc_check_info(info);
	if (error)
	{
		ft_free_info(info);
		return (NULL);
	}
	ft_initialize_gear(info);
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (NULL);
}
