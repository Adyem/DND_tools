#include "dnd_tools.hpp"
#include "veraak.hpp"
#include <iostream>

static void	ft_veraak_phase_second(t_char *info)
{
	if (info->stats.turn == 1)
		ft_cast_chaos_armor(info);
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
	return ;
}

static void	ft_veraak_phase_third(t_char *info)
{
	if (info->stats.turn == 1)
		std::cout << CHAOS_SMASH;
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
	return ;
}

static void	ft_veraak_phase_four(t_char *info)
{
	if (info->stats.turn == 1)
		std::cout << CHAOS_BREATH;
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
	return ;
}

static void	ft_veraak_phase_five(t_char *info)
{
	if (info->stats.turn == 1)
		ft_cast_chaos_armor(info);
	else if (info->stats.turn == 2)
		std::cout << CHAOS_SMASH;
	else if (info->stats.turn == 3)
		std::cout << CHAOS_BREATH;
	else if (info->stats.turn == 5)
		info->stats.turn = 0;
	info->stats.turn++;
	return ;
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
	else if (info->stats.phase != 1)
		std::cerr << "242-" << info->name << " phase counter out of bounds\n";
	return ;
}