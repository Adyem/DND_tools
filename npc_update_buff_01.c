#include "dnd_tools.h"

void ft_update_buff_status(t_char *info, int current_dur, int duration, const char *buff_name)
{
	if (duration == 0 && current_dur == 0)
		ft_printf("%s never had %s and still doesn't have it\n", info->name, buff_name);
	else if (duration == 0)
		ft_printf("%s just lost his %s buff\n", info->name, buff_name);
	else if (duration == 1 && current_dur == 0)
		ft_printf("%s just recieved a %s that lasts for a turn\n", info->name, buff_name);
	else if (duration == 1 && current_dur == 1)
		ft_printf("%s alreaddy had a %s that lasts for a turn\n", info->name, buff_name);
	else if (duration > 1 && current_dur == 0)
		ft_printf("%s just recieved a %s that lasts for %i turns\n",
			info->name, buff_name, duration);
	else if (duration > 1 && duration > current_dur)
		ft_printf("%s his %s got refreshed to %i turns\n", info->name, buff_name, duration);
	else if (duration > 1 && current_dur > duration)
		ft_printf("%s alreaddy had a better %s that lasts for %i turns\n",
			info->name, buff_name, current_dur);
	else if (duration == current_dur)
		ft_printf("%s alreaddy has a %s that is just as good lasting %i turns\n",
			info->name, buff_name, current_dur);
	return ;
}

void	ft_npc_update_buff(t_char *info, const char **input, int *buff, const char *name)
{
	int	number;

	if (ft_check_value(input[2]))
	{
		ft_printf_fd(2, "1-Buff Error: Expecting a number between 0 and 50\n");
		return ;
	}
	number = ft_atoi(input[2]);
	if (number >= 0 && number <= 50)
	{
		ft_update_buff_status(info, *buff, number, name);
		if (number > *buff)
			*buff = number;
		else if (number == 0)
			*buff = number;
	}
	else
		ft_printf_fd(2, "2-Buff Error: Expecting a number between 0 and 50\n");
	return ;
}
