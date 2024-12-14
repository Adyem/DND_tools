#include "dnd_tools.hpp"
#include "veraak.hpp"
#include "libft/Printf/printf.hpp"

static void	ft_veraak_phase_second(SharedPtr<t_char> info)
{
	if (info->stats.turn == 1)
		ft_cast_chaos_armor(info);
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
	return ;
}

static void	ft_veraak_phase_third(SharedPtr<t_char> info)
{
	if (info->stats.turn == 1)
		pf_printf(CHAOS_SMASH);
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
	return ;
}

static void	ft_veraak_phase_four(SharedPtr<t_char> info)
{
	if (info->stats.turn == 1)
		pf_printf(CHAOS_BREATH);
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
	return ;
}

static void	ft_veraak_phase_five(SharedPtr<t_char> info)
{
	if (info->stats.turn == 1)
		ft_cast_chaos_armor(info);
	else if (info->stats.turn == 2)
		pf_printf(CHAOS_SMASH);
	else if (info->stats.turn == 3)
		pf_printf(CHAOS_BREATH);
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
	return ;
}

void	ft_veraak_check_phase(SharedPtr<t_char> info)
{
	if (info->stats.phase == 2)
		ft_veraak_phase_second(info);
	else if (info->stats.phase == 3)
		ft_veraak_phase_third(info);
	else if (info->stats.phase == 4)
		ft_veraak_phase_four(info);
	else if (info->stats.phase == 5)
		ft_veraak_phase_five(info);
	else if (info->stats.phase != 1)
		pf_printf_fd(2, "242-%s phase counter out of bounds\n", info->name);
	return ;
}
