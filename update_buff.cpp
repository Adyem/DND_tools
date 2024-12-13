#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

static void	ft_update_buff_duration(SharedPtr<t_char>info, const char *buff_name, int duration)
{
	if (duration == 0)
		pf_printf("%s just lost his %s buff\n", info->name, buff_name);
	else if (duration == 1)
		pf_printf("%s has a single turn of %s left\n", info->name, buff_name);
	else
		pf_printf("%s has %d turns left on his %s buff\n", info->name, duration, buff_name);
	return ;
}

static void	ft_update_buf_duration(SharedPtr<t_char>info, const char *buf_name, int *duration)
{
	(*duration)--;
	ft_update_buff_duration(info, buf_name, *duration);
}

void	ft_update_buf(SharedPtr<t_char>info)
{
	if (info->bufs.bless.duration > 0)
		ft_update_buf_duration(info, "bless", &info->bufs.bless.duration);
	if (info->bufs.lightning_strike.duration > 0)
		ft_update_lightning_strike(info);
	if (info->bufs.lightning_strikeV2.duration > 0)
		ft_update_lightningV2_strike(info);
	if (info->bufs.protective_winds.duration > 0)
		ft_update_buf_duration(info, "protective winds", &info->bufs.protective_winds.duration);
	if (info->bufs.flame_geyser.duration > 0)
		ft_update_flame_geyser(info);
	if (info->bufs.meteor_strike.duration > 0)
		ft_update_meteor_strike(info);
	if (info->bufs.earth_pounce.active == 1)
		ft_update_earth_pounce(info);
	if (info->bufs.arcane_pounce.active == 1)
		ft_update_arcane_pounce(info);
	if (info->bufs.frost_breath.active == 1)
		ft_update_frost_breath(info);
	if (info->bufs.chaos_armor.duration > 0)
	{
		ft_update_buf_duration(info, "chaos armor", &info->bufs.chaos_armor.duration);
		info->concentration.duration = info->bufs.chaos_armor.duration;
		if (info->concentration.duration)
			ft_remove_concentration(info);
	}
	return ;
}
