#include "dnd_tools.h"

static int	ft_calculate_ac(t_char *info)
{
	int	ac;

	ac = 10 + ((info->stats.dex - 10) / 2);
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

void	ft_npc_check_ac(t_char *info, char **input)
{
	int	number;
	int	ac;

	ac = ft_calculate_ac(info);
	if (ft_strcmp_dnd(input[2], "crit") == 0)
	{
		if (info->bufs.protective_winds.duration > 0)
			ft_printf("%s has protective winds running anny projectiles are thrown " \
					"back at the attacker\n", info->name);
		ft_printf("%s was hit by a critical strike\n", info->name);
		return ;
	}
	else if (ft_check_value(input[2]))
	{
		ft_printf_fd(2, "1-to hitexpecting a number between 1 and 99 or " \
				"the word \'crit\'\n");
		return ;
	}
	number = ft_atoi(input[2]);
	if (number >= 0 && number <= 99)
	{
		if (info->bufs.protective_winds.duration > 0)
			ft_printf("%s has protective winds running anny projectiles are thrown " \
					"back at the attacker\n", info->name);
		if (ac <= number)
			ft_printf("%s was hit by the attack\n", info->name);
		else
			ft_printf("the attack missed %s\n", info->name);
	}
	else
		ft_printf_fd(2, "2-to hit expecting a number between 1 and 99 or " \
				"the word \'crit\'\n");
}
