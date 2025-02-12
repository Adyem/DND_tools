#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/math.hpp"
#include "libft/Template/shared_ptr.hpp"

int ft_weapon_find_stat(t_char * info, t_equipment_id *weapon)
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
        return ft_max(ft_calculate_str(info), ft_calculate_dex(info));
    return (0);
}

void ft_check_dice_amount_and_faces(t_equipment_id *weapon, t_damage_info *d_info,
                                           int offhand, t_char * info)
{
    d_info->dice_amount = weapon->attack.effect_dice_amount;
    d_info->dice_faces = weapon->attack.effect_dice_faces;
    if (offhand && weapon->slot == (SLOT_WEAPON | SLOT_OFFHAND_WEAPON))
    {
        d_info->dice_amount = weapon->attack.effect_secund_dice_amount;
        d_info->dice_faces = weapon->attack.effect_secund_dice_faces;
    }
    else if (!offhand && weapon->slot == SLOT_WEAPON
             && info->equipment.offhand_weapon.equipment_id == 0)
    {
        d_info->dice_amount = weapon->attack.effect_dice_amount;
        d_info->dice_faces = weapon->attack.effect_dice_faces;
    }
    return ;
}

void ft_calculate_damage(t_equipment_id *weapon, t_damage_info *d_info, bool is_crit)
{
    int multiplier;

    if (is_crit)
        multiplier = 2;
    else
        multiplier = 1;
    d_info->damage = ft_dice_roll(d_info->dice_amount * multiplier, d_info->dice_faces)
                     + d_info->stat_mod;
    pf_printf("deals %d %s damage\n", d_info->damage, weapon->attack.damage_type);
    return ;
}
