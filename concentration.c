#include "dnd_tools.h"

static void	ft_concentration_remove_buf(t_char *info, t_char *target)
{
	if (DEBUG == 1)
	{
	    ft_printf("Memory address of info struct: %p\n", (void *)info);
		ft_printf("Memory address of target struct: %p\n", (void *)target);
	}
	if (info->concentration.spell_id == HUNTERS_MARK_ID)
		ft_concentration_remove_hunters_mark(info, target);
	else if (info->concentration.spell_id == CHAOS_ARMOR_ID)
		info->bufs.chaos_armor.duration = 0;
	return ;
}

int ft_remove_concentration(t_char *info)
{
    int i;
    t_char *target;
    int fd;

    i = 0;
    while (info->concentration.targets && info->concentration.targets[i])
	{
		if (ft_set_stats_check_name(info->concentration.targets[i]))
		{
			if (ft_check_player_character(info->concentration.targets[i]) == 0)
			{
				target = NULL;
				i++;
				continue;
			} 
			else
				target = NULL;
		}
		else
		{
			target = ft_get_info(info->concentration.targets[i], info->struct_name);
			if (!target)
                return ft_printf_fd(2, "300-Error getting info %s\n", info->concentration.targets[i]);
        }
        if (target)
		{
            ft_concentration_remove_buf(info, target);
            fd = open(target->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            if (fd == -1)
			{
                ft_free_info(target);
                return ft_printf_fd(2, "301-Error opening %s: %s\n", info->save_file, strerror(errno));
            }
            ft_npc_write_file(target, &target->stats, &info->c_resistance, fd);
            ft_free_info(target);
            close(fd);
        }
        i++;
    }
    info->concentration.concentration = 0;
    info->concentration.spell_id = 0;
    info->concentration.dice_amount_mod = 0;
    info->concentration.dice_faces_mod = 0;
    info->concentration.base_mod = 0;
    ft_free_double_char(info->concentration.targets);
    info->concentration.targets = NULL;
    return 0;
}

void	ft_check_concentration(t_char *info, int damage)
{
	int	difficulty;
	int	result;

	if (DEBUG == 1)
		ft_printf("Rolling con save for concentration %s\n", info->name);
	if (info->version_number < 2 || !info->concentration.concentration)
	{
		if (info->version_number < 2)
			ft_printf("%s doesn't support concentration\n", info->name);
		return ;
	}
	result = ft_saving_throw(info, "constitution", info->stats.con, info->save_mod.con);
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
