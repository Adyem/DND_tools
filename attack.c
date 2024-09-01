#include "dnd_tools.h"

typedef struct s_damage_info
{
    int mod;
    int result;
    int damage;
	int	stat_mod;
} t_damage_info;

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
		if (ft_calculate_str(info) > ft_calculate_dex(info))
			return (ft_calculate_str(info));
		else
			return (ft_calculate_dex(info));
	}
	return (0);
}

static void	ft_weapon_attack_crit(t_char *info, t_equipment_id *weapon,
				t_damage_info *d_info)
{
	ft_check_buff_damage(info);
	ft_printf("a crit (%i) and ", d_info->result);
	d_info->damage = ft_dice_roll(weapon->attack.effect_dice_amount * 2,
			weapon->attack.effect_dice_faces) + d_info->stat_mod;
	ft_printf("deals %i %s damage\n", d_info->damage, weapon->attack.damage_type);
}

static void	ft_weapon_attack_non_crit(t_char *info, t_equipment_id *weapon,
				t_damage_info *d_info)
{
	ft_check_buff_damage(info);
	ft_printf("%i+%i+%i+%i for a total of %i and ",
		d_info->result, d_info->stat_mod, info->attack_bonus.attack_bonus, d_info->mod, d_info->result
		+ d_info->stat_mod + d_info->mod + info->attack_bonus.attack_bonus);
	d_info->damage = ft_dice_roll(weapon->attack.effect_dice_amount,
			weapon->attack.effect_dice_faces) + d_info->stat_mod;
	ft_printf("deals %i %s damage\n", d_info->damage, weapon->attack.damage_type);
}

void	ft_weapon_attack(t_char *info, t_equipment_id *weapon)
{
	t_damage_info d_info;

	if (!weapon->attack.function)
	{
		ft_printf_fd(2, "162-Error no attack set for %s", weapon->name);
		return ;
	}
	d_info.stat_mod = (ft_weapon_find_stat(info, weapon) - 10) / 2;
	d_info.result = ft_dice_roll(1, 20);
	if (d_info.result == -1)
	{
		ft_printf_fd(2, "101-Error: dice rolling error in attack");
		return ;
	}
	d_info.mod = ft_attack_roll_check_buffs(info, &d_info.result);
	if (weapon->projectile_name)
		ft_printf("%s uses his/her %s to fire a %s and rolled ",
			info->name, weapon->name, weapon->projectile_name);
	else 
		ft_printf("%s attacks with his\\her %s and rolled ", info->name,
			weapon->name);
	if (d_info.result <= 1 + info->crit.attack_fail)
		ft_printf("a critical fail (%i) and missed on his attack\n",
			d_info.result);
	else if (d_info.result >= 20 - info->crit.attack)
		ft_weapon_attack_crit(info, weapon, &d_info);
	else
		ft_weapon_attack_non_crit(info, weapon, &d_info);
	return ;
}
