#include "dnd_tools.h"

int	ft_npc_check_info(t_char *info)
{
	int	error;

	error = 0;
	if (info->stats.health <= -1 || info->stats.health > info->dstats.health)
		error += ft_printf_fd(2, "%s health value not found\n", info->name);
	if (info->stats.health <= -1 || info->stats.temp_hp > 5000)
		error += ft_printf_fd(2, "%s temp health value not found\n", info->name);
	if (info->stats.ac <= -1)
		error += ft_printf_fd(2, "%s armor class value not found\n", info->name);
	if (info->stats.str <= -1 || info->stats.str > 30)
		error += ft_printf_fd(2, "%s strength value not found\n", info->name);
	if (info->stats.dex <= -1 || info->stats.dex > 30)
		error += ft_printf_fd(2, "%s dexterity value not found\n", info->name);
	if (info->stats.con <= -1 || info->stats.con > 30)
		error += ft_printf_fd(2, "%s constitution value not found\n", info->name);
	if (info->stats.inte <= -1 || info->stats.inte > 30)
		error += ft_printf_fd(2, "%s intelligence value not found\n", info->name);
	if (info->stats.wis <= -1 || info->stats.wis > 30)
		error += ft_printf_fd(2, "%s wisdom value not found\n", info->name);
	if (info->stats.cha <= -1 || info->stats.wis > 30)
		error += ft_printf_fd(2, "%s charisma value not found\n", info->name);
	if (info->stats.turn <= -1 || info->stats.turn > 30)
		error += ft_printf_fd(2, "%s turn value not found\n", info->name);
	if (info->stats.phase <= -1 || info->stats.turn > 30)
		error += ft_printf_fd(2, "%s phase value not found\n", info->name);
	if (info->bufs.bless.duration < 0 || info->bufs.bless.duration > 50)
		error += ft_printf_fd(2, "%s bless value outside of bounds\n", info->name);
	if (error)
		ft_printf_fd(2, "2-%s Error with the save file, please reinitialize it with the "\
			" correct values\n", info->name);
	return (error);
}
