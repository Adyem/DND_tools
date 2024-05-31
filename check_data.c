#include "dnd_tools.h"

int	ft_npc_check_info_2(t_char *info)
{
	int	error;

	error = 0;
	if (info->version_number < 2)
		return (0);
	if (info->c_resistance.acid < -500 || info->c_resistance.acid > 500)
		error += ft_printf_fd(2, "%s acid resistance value not found\n", info->name);
	if (info->c_resistance.bludgeoning < -500 || info->c_resistance.bludgeoning > 500)
		error += ft_printf_fd(2, "%s bludgeoning resistance value not found\n",
				info->name);
	if (info->c_resistance.cold < -500 || info->c_resistance.cold > 500)
		error += ft_printf_fd(2, "%s cold resistance value not found\n", info->name);
	if (info->c_resistance.fire < -500 || info->c_resistance.fire > 500)
		error += ft_printf_fd(2, "%s fire resistance value not found\n", info->name);
	if (info->c_resistance.force < -500 || info->c_resistance.force > 500)
		error += ft_printf_fd(2, "%s force resistance value not found\n", info->name);
	if (info->c_resistance.lightning < -500 || info->c_resistance.lightning > 500)
		error += ft_printf_fd(2, "%s lightning resistance value not found\n", info->name);
	if (info->c_resistance.necrotic < -500 || info->c_resistance.necrotic > 500)
		error += ft_printf_fd(2, "%s necrotic resistance value not found\n", info->name);
	if (info->c_resistance.piercing < -500 || info->c_resistance.piercing > 500)
		error += ft_printf_fd(2, "%s piercing resistance value not found\n", info->name);
	if (info->c_resistance.poison < -500 || info->c_resistance.poison > 500)
		error += ft_printf_fd(2, "%s poison resistance value not found\n", info->name);
	if (info->c_resistance.psychic < -500 || info->c_resistance.psychic > 500)
		error += ft_printf_fd(2, "%s psychic resistance value not found\n", info->name);
	if (info->c_resistance.radiant < -500 || info->c_resistance.radiant > 500)
		error += ft_printf_fd(2, "%s radiant resistance value not found\n", info->name);
	if (info->c_resistance.slashing < -500 || info->c_resistance.slashing > 500)
		error += ft_printf_fd(2, "%s slashing resistance value not found\n", info->name);
	if (info->c_resistance.thunder < -500 || info->c_resistance.thunder > 500)
		error += ft_printf_fd(2, "%s thunder resistance value not found\n", info->name);
	if (info->concentration.concentration < 0)
        error += ft_printf_fd(2, "%s concentration value is negative\n", info->name);
    if (info->concentration.spell_id < 0)
        error += ft_printf_fd(2, "%s spell_id value is negative\n", info->name);
    if (info->concentration.dice_amount_mod < 0)
        error += ft_printf_fd(2, "%s dice_amount_mod value is negative\n", info->name);
    if (info->concentration.dice_faces_mod < 0)
        error += ft_printf_fd(2, "%s dice_faces_mod value is negative\n", info->name);
    if (info->concentration.base_mod < 0)
        error += ft_printf_fd(2, "%s base_mod value is negative\n", info->name);
    if (info->concentration.duration < 0)
        error += ft_printf_fd(2, "%s duration value is negative\n", info->name);
	return (error);
}

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
	if (info->initiative < -50)
		error += ft_printf_fd(2, "%s initiative value outside of bounds\n", info->name);
	if (info->bufs.lightning_strike.duration <  0)
		error += ft_printf_fd(2, "%s lightning strike duration outside of bounds\n", info->name);
	if (info->bufs.protective_winds.duration < 0)
		error += ft_printf_fd(2, "%s protective winds duration outside of bounds\n", info->name);
	error += ft_npc_check_info_2(info);
	if (error)
		ft_printf_fd(2, "2-%s Error with the save file, please reinitialize it with the "\
			" correct values\n", info->name);
	return (error);
}
