#include "dnd_tools.hpp"
#include "libft/printf/ft_printf.hpp"
#include "libft/printf_fd/ft_printf_fd.hpp"
#include "chaos_goblin.hpp"

void	ft_chaos_goblin_turn(t_char *info)
{
	ft_update_buf(info);
	if (!info->concentration.concentration && ft_dice_roll(1, 6) > 3)
		ft_cast_chaos_armor(info);
	if (info->flags.prone)
	{
		ft_printf("%s will use his/her action to stand up\n", info->name);
		info->flags.prone = 0;
	}
	else
		ft_printf("The chaos_goblin will try to make either a ranged or melee attack during his turn\n");
	ft_printf("Chaos_goblin currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
}

static void	ft_initialize_gear_and_feats(t_char *info)
{
	(void)info;
	return ;
}

t_char	*ft_chaos_goblin(const int index, const char **input, t_name *name, int exception)
{
	int		error;
	t_char	*info;

	info = (t_char *)calloc(1, sizeof(t_char));
	if (!info)
	{
		ft_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
		return (NULL);
	}
	*info = CHAOS_GOBLIN_INFO;
	info->name = input[0];
	info->struct_name = name;
	info->save_file = ft_strjoin("data/", input[0]);
	if (!info->save_file)
	{
		ft_printf_fd(2, "104-Error: Failed to allocate memory save_file name%s\n", info->name);
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
	ft_initialize_gear_and_feats(info);
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (NULL);
}
