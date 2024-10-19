#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/Printf/ft_printf.hpp"
#include <algorithm>

typedef struct s_damage_info
{
    int mod;
    int result;
    int damage;
    int stat_mod;
    int dice_amount;
    int dice_faces;
} t_damage_info;

static int ft_weapon_find_stat(t_char *info, t_equipment_id *weapon)
{
    if (!weapon->attack.stat)
        return (0);
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_STR) == 0)
        return (ft_calculate_str(info));
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_DEX) == 0)
        return (ft_calculate_dex(info));
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_CON) == 0)
        return (ft_calculate_con(info));
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_INT) == 0)
        return (ft_calculate_inte(info));
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_WIS) == 0)
        return (ft_calculate_wis(info));
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_CHA) == 0)
        return (ft_calculate_cha(info));
    if (ft_strcmp_dnd(weapon->attack.stat, FINESSE) == 0)
        return std::max(ft_calculate_str(info), ft_calculate_dex(info));
    return (0);
}

static void ft_check_dice_amount_and_faces(t_equipment_id *weapon, t_damage_info *d_info, int offhand, t_char *info)
{
    d_info->dice_amount = weapon->attack.effect_dice_amount;
    d_info->dice_faces = weapon->attack.effect_dice_faces;
    if (offhand && weapon->slot == (SLOT_WEAPON | SLOT_OFFHAND_WEAPON))
    {
        d_info->dice_amount = weapon->attack.effect_secund_dice_amount;
        d_info->dice_faces = weapon->attack.effect_secund_dice_faces;
    }
    else if (!offhand && weapon->slot == SLOT_WEAPON && info->equipment.offhand_weapon.equipment_id == 0)
    {
        d_info->dice_amount = weapon->attack.effect_dice_amount;
        d_info->dice_faces = weapon->attack.effect_dice_faces;
    }
	return ;
}

static void ft_print_attack_roll(t_char *info, t_equipment_id *weapon, t_damage_info *d_info)
{
    if (weapon->projectile_name)
        ft_printf("%s uses his/her %s to fire a %s and rolled ", info->name, weapon->name, weapon->projectile_name);
    else
        ft_printf("%s attacks with his/her %s and rolled ", info->name, weapon->name);
    if (d_info->result <= 1 + info->crit.attack_fail)
    {
        ft_printf("a critical fail (%d) and missed on his attack\n", d_info->result);
        return ;
    }
	return ;
}

static void ft_calculate_damage(t_equipment_id *weapon, t_damage_info *d_info, bool is_crit)
{
    int multiplier = is_crit ? 2 : 1;
    d_info->damage = ft_dice_roll(d_info->dice_amount * multiplier, d_info->dice_faces) + d_info->stat_mod;
    ft_printf("deals %d %s damage\n", d_info->damage, weapon->attack.damage_type);
	return ;
}

static void ft_handle_attack_result(t_char *info, t_equipment_id *weapon, t_damage_info *d_info)
{
    if (d_info->result >= 20 - info->crit.attack)
    {
        ft_check_buff_damage(info);
        ft_printf("a crit (%d) and ", d_info->result);
        ft_calculate_damage(weapon, d_info, true);
    }
    else
    {
        ft_check_buff_damage(info);
        ft_printf("(%d)+%d+%d+%d for a total of %d and ", d_info->result, d_info->stat_mod,
				info->attack_bonus.attack_bonus, d_info->mod, (d_info->result +
				d_info->stat_mod + d_info->mod + info->attack_bonus.attack_bonus));
        ft_calculate_damage(weapon, d_info, false);
    }
	return ;
}

void ft_weapon_attack(t_char *info, t_equipment_id *weapon, int offhand)
{
    t_damage_info d_info;

    d_info.stat_mod = (ft_weapon_find_stat(info, weapon) - 10) / 2;
    d_info.result = ft_dice_roll(1, 20);
    if (d_info.result == -1)
    {
        ft_printf_fd(2, "101-Error: dice rolling error in attack\n");
        return ;
    }
    d_info.mod = ft_attack_roll_check_buffs(info, &d_info.result);
    ft_print_attack_roll(info, weapon, &d_info);
    ft_check_dice_amount_and_faces(weapon, &d_info, offhand, info);
    ft_handle_attack_result(info, weapon, &d_info);
	return ;
}
