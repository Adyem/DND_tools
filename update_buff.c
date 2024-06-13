#include "dnd_tools.h"

static void	ft_update_buff_duration(t_char *info, char *buff_name, int duration)
{
	if (duration == 0)
		ft_printf("%s just lost his %s buf\n", info->name, buff_name);
	else if (duration == 1)
		ft_printf("%s has a single turn of %s left\n", info->name, buff_name);
	else
		ft_printf("%s has %i turns left on his %s buf\n",
				info->name, duration, buff_name);
	return ;
}

static void	ft_update_buf_duration(t_char *info, char *buf_name, int *duration)
{
	(*duration)--;
	ft_update_buff_duration(info, buf_name, *duration);
}

void	ft_update_buf(t_char *info)
{
	if (info->bufs.bless.duration > 0)
		ft_update_buf_duration(info, "bless", &info->bufs.bless.duration);
	if (info->bufs.lightning_strike.duration > 0)
		ft_update_lightning_strike(info);
	if (info->bufs.protective_winds.duration > 0)
		ft_update_buf_duration(info, "protective winds",
			&info->bufs.protective_winds.duration);
	if (info->bufs.chaos_armor.duration > 0)
	{
		ft_update_buf_duration(info, "chaos armor", &info->bufs.chaos_armor.duration);
		info->concentration.duration = info->bufs.chaos_armor.duration;
		if (info->concentration.duration)
			ft_remove_concentration(info);
	}
	return ;
}
