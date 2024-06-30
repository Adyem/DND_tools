#include "dnd_tools.h"

static int	ft_weapon_find_stat(t_char *info, t_equipment_id *weapon)
{
	if (!weapon->attack.stat)
		return (0);
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_STR) == 0)
		return (info->stats.str);
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_DEX) == 0)
		return (info->stats.dex);
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_CON) == 0)
		return (info->stats.con);
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_INT) == 0)
		return (info->stats.inte);
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_WIS) == 0)
		return (info->stats.wis);
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_CHA) == 0)
		return (info->stats.cha);
	return (0);
}

void	ft_weapon_attack(t_char *info, t_equipment_id *weapon)
{
	int	mod;
	int	stat_mod;
	int	result;
	int	damage;

	stat_mod = ft_weapon_find_stat(info, weapon);
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("%s attacks with his\\her %s and rolled ", info->name,
			weapon->name);
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_check_buff_damage(info);
		ft_printf("a crit (%i) and ", result);
		damage = ft_dice_roll(weapon->attack.effect_dice_amount * 2,
				weapon->attack.effect_dice_faces) + stat_mod;
		ft_printf("deals %i %s damage\n", damage, weapon->attack.damage_type);
	}
	else
	{
		ft_check_buff_damage(info);
		ft_printf("%i+%i+%i+%i for a total of %i and ",
			result, stat_mod, info->attack_bonus.attack_bonus, mod, result
			+ stat_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(weapon->attack.effect_dice_amount,
				weapon->attack.effect_dice_faces) + stat_mod;
		ft_printf("deals %i %s damage\n", damage, weapon->attack.damage_type);
	}
	return ;
}
