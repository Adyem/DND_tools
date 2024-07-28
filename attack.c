#include "dnd_tools.h"
#include "identification.h"

static int	ft_weapon_find_stat(t_char *info, t_equipment_id *weapon)
{
	if (!weapon->attack.stat)
		return (0);
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_STR) == 0)
		return (ft_calculate_str(info));
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_DEX) == 0)
		return (ft_calculate_dex(info));
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_CON) == 0)
		return (ft_calculate_con(info));
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_INT) == 0)
		return (ft_calculate_inte(info));
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_WIS) == 0)
		return (ft_calculate_wis(info));
	else if (ft_strcmp_dnd(weapon->attack.stat, STAT_CHA) == 0)
		return (ft_calculate_cha(info));
	else if (ft_strcmp_dnd(weapon->attack.stat, FINESSE) == 0)
	{
		if (info->stats.str > info->stats.dex)
			return (info->stats.str);
		else
			return (info->stats.dex);
	}
	return (0);
}

void	ft_weapon_attack(t_char *info, t_equipment_id *weapon)
{
	int	mod;
	int	stat_mod;
	int	result;
	int	damage;

	if (!weapon->attack.function)
	{
		ft_printf_fd(2, "162-Error no attack set for %s", weapon->name);
		return ;
	}
	stat_mod = (ft_weapon_find_stat(info, weapon) - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	if (weapon->projectile_name)
		ft_printf("%s uses his/her %s to fire a %s and rolled ",
			info->name, weapon->name, weapon->projectile_name);
	else 
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
