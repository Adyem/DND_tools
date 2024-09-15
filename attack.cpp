#include "dnd_tools.hpp"
#include "identification.hpp"
#include <iostream>

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
	std::cout << "a crit (" << d_info->result <<  ") and ";
	d_info->damage = ft_dice_roll(weapon->attack.effect_dice_amount * 2,
			weapon->attack.effect_dice_faces) + d_info->stat_mod;
	std::cout << "deals " << d_info->damage << weapon->attack.damage_type << " damage" << std::endl;
}

static void ft_weapon_attack_non_crit(t_char *info, t_equipment_id *weapon,
	t_damage_info *d_info)
{
    ft_check_buff_damage(info);
    std::cout << d_info->result << "+" << d_info->stat_mod << "+"
		<< info->attack_bonus.attack_bonus << "+" << d_info->mod
        << " for a total of " << (d_info->result + d_info->stat_mod
		+ d_info->mod + info->attack_bonus.attack_bonus) << " and ";
    d_info->damage = ft_dice_roll(weapon->attack.effect_dice_amount,
			weapon->attack.effect_dice_faces) + d_info->stat_mod;
    std::cout << "deals " << d_info->damage << " " << weapon->attack.damage_type
		<< " damage" << std::endl;
	return ;
}

void ft_weapon_attack(t_char *info, t_equipment_id *weapon)
{
    t_damage_info d_info;
    bool is_offhand = false;
    bool is_one_handed_weapon = weapon->slot & SLOT_WEAPON && weapon->slot & SLOT_OFFHAND_WEAPON;
    
    if (info->equipment.offhand_weapon.slot != SLOT_NONE && 
        info->equipment.offhand_weapon.equipment_id != 0 &&
        is_one_handed_weapon)
    {
        is_offhand = true;
    }
    if (!weapon->attack.function)
    {
        std::cerr << "Error: No attack set for " << weapon->name << std::endl;
        return;
    }
    d_info.stat_mod = (ft_weapon_find_stat(info, weapon) - 10) / 2;
    d_info.result = ft_dice_roll(1, 20);
    if (d_info.result == -1)
    {
        std::cerr << "Error: Dice rolling error in attack" << std::endl;
        return;
    }

    d_info.mod = ft_attack_roll_check_buffs(info, &d_info.result);
    if (weapon->projectile_name)
        std::cout << info->name << " uses their " << weapon->name << " to fire a " 
                  << weapon->projectile_name << " and rolled ";
    else
        std::cout << info->name << " attacks with their " << weapon->name << " and rolled ";
    if (d_info.result <= 1 + info->crit.attack_fail)
    {
        std::cout << "a critical fail (" << d_info.result << ") and missed the attack" << std::endl;
        return;
    }
    if (d_info.result >= 20 - info->crit.attack)
    {
        if (is_offhand)
        {
            std::cout << "(Offhand attack) a crit (" << d_info.result << ") and ";
            d_info.damage = ft_dice_roll(weapon->attack.effect_secund_dice_amount * 2,
                                         weapon->attack.effect_secund_dice_faces) + d_info.stat_mod;
            std::cout << "deals " << d_info.damage << " " << weapon->attack.damage_type
                      << " damage" << std::endl;
        }
        else
            ft_weapon_attack_crit(info, weapon, &d_info);
        return;
    }
    if (is_offhand)
    {
        std::cout << "(Offhand attack) ";
        d_info.damage = ft_dice_roll(weapon->attack.effect_secund_dice_amount,
                                     weapon->attack.effect_secund_dice_faces) + d_info.stat_mod;
        std::cout << "deals " << d_info.damage << " " << weapon->attack.damage_type
                  << " damage" << std::endl;
    }
    else
        ft_weapon_attack_non_crit(info, weapon, &d_info);
}
