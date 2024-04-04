#include "dnd_tools.h"

int ft_set_stats_1(t_char *info, char **content, int i)
{
	int	r_value;

	r_value = 0;
	if (ft_strncmp(content[i], "HEALTH=", 7) == 0 && (info->stats.health == -1))
		info->stats.health = ft_check_stat(info, content[i], 7);
	else if (ft_strncmp(content[i], "TEMP_HP=", 8) == 0 && (info->stats.temp_hp == -1))
		info->stats.temp_hp = ft_check_stat(info, content[i], 8);
	else if (ft_strncmp(content[i], "AC=", 3) == 0 && (info->stats.ac == -1))
		info->stats.ac = ft_check_stat(info, content[i], 3);
	else if (ft_strncmp(content[i], "STR=", 4) == 0 && (info->stats.str == -1))
		info->stats.str = ft_check_stat(info, content[i], 4);
	else if (ft_strncmp(content[i], "DEX=", 4) == 0 && (info->stats.dex == -1))
		info->stats.dex = ft_check_stat(info, content[i], 4);
	else if (ft_strncmp(content[i], "CON=", 4) == 0 && (info->stats.con == -1))
		info->stats.con = ft_check_stat(info, content[i], 4);
	else if (ft_strncmp(content[i], "INT=", 4) == 0 && (info->stats.inte == -1))
		info->stats.inte = ft_check_stat(info, content[i], 4);
	else if (ft_strncmp(content[i], "WIS=", 4) == 0 && (info->stats.wis == -1))
		info->stats.wis = ft_check_stat(info, content[i], 4);
	else if (ft_strncmp(content[i], "CHA=", 4) == 0 && (info->stats.cha == -1))
		info->stats.cha = ft_check_stat(info,content[i], 4);
	else if (ft_strncmp(content[i], "TURN=", 5) == 0 && (info->stats.turn == -1))
		info->stats.turn = ft_check_stat(info, content[i], 5);
	else if (ft_strncmp(content[i], "INITIATIVE=", 11) == 0 && (info->initiative == -1))
		info->initiative = ft_check_stat(info, content[i], 11);
	else if (ft_strncmp(content[i], "BLESS_DUR=", 10) == 0
			&& (info->bufs.bless.duration == 0))
		info->bufs.bless.duration = ft_check_stat(info, content[i], 10);
	else if(ft_strncmp(content[i], "PHASE=", 6) == 0 && (info->stats.phase== -1))
		info->stats.phase = ft_check_stat(info, content[i], 6);
	else if (ft_strncmp(content[i], "LIGHTNING_STRIKE_DUR=", 21) == 0)
		info->bufs.lightning_strike.duration = ft_check_stat(info, content[i], 21);
	else if (ft_strncmp(content[i], "PROTECTIVE_WINDS_DUR=", 21) == 0)
		info->bufs.protective_winds.duration = ft_check_stat(info, content[i], 21);
	else
		r_value = 1;
	return(r_value);
}

int	ft_set_stats(t_char *info, char **content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (ft_set_stats_1(info, content, i) == 0)
		{
			i++;
			continue ;
		}
		else
		{
			ft_printf_fd(2, "Something is wrong with the save file for Maverick at the "\
				"line: %s, please reinitialize the save\n", content[i]);
			ft_free_content(content);
			return (1);
		}
		i++;
	}
	return (0);
}
