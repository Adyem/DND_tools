#include "dnd_tools.h"

int	ft_remove_concentration(t_char *info)
{
	int		i;
	t_char	*target;
	int		fd;

	i = 0;
	while (info->concentration.targets && info->concentration.targets[i])
	{
		if (ft_set_stats_check_name(info->concentration.targets[i]))
		{
			i++;
			continue ;
		}
		target = ft_get_info(info->concentration.targets[i], info->struct_name);
		if (!target)
			return (ft_printf_fd(2, "300-Error getting info %s\n",
					info->concentration.targets[i]));
		fd = open(target->save_file, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
		if (fd == -1)
			return (ft_printf_fd(2, "301-Error opening %s: %s\n",
					info->save_file, strerror(errno)));
		ft_npc_write_file(target, &target->stats, &info->c_resistance, fd);
		close(fd);
		break ;
	}
	info->concentration.concentration = 0;
	info->concentration.spell_id = 0;
	info->concentration.dice_amount_mod = 0;
	info->concentration.dice_faces_mod = 0;
	info->concentration.base_mod = 0;
	ft_free_double_char(info->concentration.targets);
	info->concentration.targets = NULL;
	return (0);
}

void	ft_check_concentration(t_char *info, int damage)
{
	int	difficulty;
	int	result;

	if (info->version_number < 2 || !info->concentration.concentration)
		return ;
	result = ft_saving_throw(info, "constituion", info->stats.con, info->save_mod.con);
	difficulty = 10;
	if (difficulty < damage / 2)
		difficulty = damage / 2;
	if (result < difficulty)
	{
		ft_printf("%s failed on his/her concentration save\n", info->name);
		ft_remove_concentration(info);
	}
	else
		ft_printf("%s made his/her concentration save\n", info->name);
	return ;
}
