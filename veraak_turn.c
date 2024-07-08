#include "dnd_tools.h"
#include "veraak.h"

static void	ft_veraak_phase_second(t_char *info)
{
	if (info->stats.turn == 1)
		ft_cast_chaos_armor(info);
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
}

static void	ft_veraak_phase_third(t_char *info)
{
	if (info->stats.turn == 1)
		ft_printf("%s", CHAOS_SMASH);
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
}

static void	ft_veraak_phase_four(t_char *info)
{
	if (info->stats.turn == 1)
		ft_printf("%s", CHAOS_BREATH);
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
}

static void	ft_veraak_phase_five(t_char *info)
{
	if (info->stats.turn == 1)
		ft_cast_chaos_armor(info);
	else if (info->stats.turn == 2)
		ft_printf("%s", CHAOS_SMASH);
	else if (info->stats.turn == 3)
		ft_printf("%s", CHAOS_BREATH);
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
}

void	ft_veraak_check_phase(t_char *info)
{
	if (info->stats.phase == 2)
		ft_veraak_phase_second(info);
	else if (info->stats.phase == 3)
		ft_veraak_phase_third(info);
	else if (info->stats.phase == 4)
		ft_veraak_phase_four(info);
	else if (info->stats.phase == 5)
		ft_veraak_phase_five(info);
	else
		ft_printf_fd(2, "242-%s phase counter out of bounds", info->name);
}
