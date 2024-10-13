#include "dnd_tools.hpp"
#include "maverick.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CMA/CMA.hpp"

void	ft_maverick_turn(t_char *info)
{
	int		first;
	int		second;

	ft_update_buf(info);
	ft_printf("\n\n");
	first = 0;
	second = 0;
	while (first == second)
	{
		first = ft_dice_roll(1, 8);
		second = ft_dice_roll(1, 8);
	}
	ft_maverick_print_f(first, second, info);
	ft_maverick_print_s(first, second, info);
	ft_printf("\n\n");
	return ;
}

static void ft_initialize_gear_and_feats(t_char *info)
{
	(void)info;
	return ;
}

t_char *ft_maverick(const int index, const char **input, t_name *name, int exception)
{
	int error;
	t_char *info;

	if (DEBUG == 1)
		ft_printf("exception = %d\n", exception);
	info = (t_char *)cma_calloc(1, sizeof(t_char), false);
	if (!info)
		return (nullptr);
	*info = MAVERICK_INFO;
	info->name = input[0];
	info->struct_name = name;
	info->save_file = cma_strjoin("data/", input[0], false);
	if (!info->save_file)
	{
		ft_free_info(info);
		return (nullptr);
	}
	if (index == 2)
	{
		if (ft_strcmp_dnd(input[1], "init") == 0)
		{
			ft_npc_write_file(info, &info->dstats, &info->d_resistance, -1);
			ft_printf("Stats for %s written on a file\n", info->name);
			ft_free_info(info);
			return (nullptr);
		}
	}
	error = ft_npc_open_file(info);
	if (error)
	{
		ft_free_info(info);
		return (nullptr);
	}
	error = ft_npc_check_info(info);
	if (error)
	{
		ft_free_info(info);
		return (nullptr);
	}
	ft_initialize_gear_and_feats(info);
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (nullptr);
}
