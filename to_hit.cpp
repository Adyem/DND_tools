#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include <iostream>

static int ft_calculate_ac(t_char *info)
{
	int ac;

	ac = 10;
	if (((info->stats.dex - 10) / 2) > info->equipment.armor.dex_ac_max_bonus)
		ac += info->equipment.armor.dex_ac_max_bonus;
	else
		ac += (info->stats.dex - 10) / 2;
	ac += info->equipment.weapon.ac;
	ac += info->equipment.offhand_weapon.ac;
	ac += info->equipment.ranged_weapon.ac;
	ac += info->equipment.armor.ac;
	ac += info->equipment.helmet.ac;
	ac += info->equipment.shield.ac;
	ac += info->equipment.boots.ac;
	ac += info->equipment.gloves.ac;
	ac += info->equipment.amulet.ac;
	ac += info->equipment.ring_01.ac;
	ac += info->equipment.ring_02.ac;
	ac += info->equipment.belt.ac;
	return (ac);
}

void ft_npc_check_ac(t_char *info, const char **input)
{
	int number;
	int ac;

	ac = ft_calculate_ac(info);
	ft_to_hit_check_buff(info);
	if (ft_strcmp_dnd(input[2], "crit") == 0)
	{
		if (info->bufs.protective_winds.duration > 0)
			std::cout << info->name 
			          << " has protective winds running, any projectiles are thrown "
			             "back at the attacker" << std::endl;
		std::cout << info->name << " was hit by a critical strike" << std::endl;
		return ;
	}
	else if (ft_check_value(input[2]))
	{
		std::cerr << "1-to hit expecting a number between 1 and 99 or the word 'crit'" << std::endl;
		return ;
	}
	number = ft_atoi(input[2]);
	if (number >= 0 && number <= 99)
	{
		if (info->bufs.protective_winds.duration > 0)
			std::cout << info->name 
			          << " has protective winds running, any projectiles are thrown "
			             "back at the attacker" << std::endl;
		if (ac <= number)
			std::cout << info->name << " was hit by the attack" << std::endl;
		else
			std::cout << "the attack missed " << info->name << std::endl;
	}
	else
		std::cerr << "2-to hit expecting a number between 1 and 99 or the word 'crit'" << std::endl;
	return ;
}
