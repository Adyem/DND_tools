#include "dnd_tools.hpp"
#include "libft/Template/shared_ptr.hpp"

int ft_calculate_crit_attack_fail_bonus(ft_sharedptr<t_char> &info)
{
    int fail_bonus = 0;

	fail_bonus += info->crit.attack_fail;
    fail_bonus += info->equipment.weapon.crit_attack_fail_bonus;
    fail_bonus += info->equipment.offhand_weapon.crit_attack_fail_bonus;
    fail_bonus += info->equipment.ranged_weapon.crit_attack_fail_bonus;
    fail_bonus += info->equipment.armor.crit_attack_fail_bonus;
    fail_bonus += info->equipment.helmet.crit_attack_fail_bonus;
    fail_bonus += info->equipment.shield.crit_attack_fail_bonus;
    fail_bonus += info->equipment.boots.crit_attack_fail_bonus;
    fail_bonus += info->equipment.gloves.crit_attack_fail_bonus;
    fail_bonus += info->equipment.amulet.crit_attack_fail_bonus;
    fail_bonus += info->equipment.ring_01.crit_attack_fail_bonus;
    fail_bonus += info->equipment.ring_02.crit_attack_fail_bonus;
    fail_bonus += info->equipment.belt.crit_attack_fail_bonus;
    return (fail_bonus);
}

int ft_calculate_crit_attack_success_bonus(ft_sharedptr<t_char> &info)
{
    int success_bonus = 0;

	success_bonus += info->crit.attack;
	success_bonus += info->equipment.weapon.crit_attack_succes_bonus;
    success_bonus += info->equipment.offhand_weapon.crit_attack_succes_bonus;
    success_bonus += info->equipment.ranged_weapon.crit_attack_succes_bonus;
    success_bonus += info->equipment.armor.crit_attack_succes_bonus;
    success_bonus += info->equipment.helmet.crit_attack_succes_bonus;
    success_bonus += info->equipment.shield.crit_attack_succes_bonus;
    success_bonus += info->equipment.boots.crit_attack_succes_bonus;
    success_bonus += info->equipment.gloves.crit_attack_succes_bonus;
    success_bonus += info->equipment.amulet.crit_attack_succes_bonus;
    success_bonus += info->equipment.ring_01.crit_attack_succes_bonus;
    success_bonus += info->equipment.ring_02.crit_attack_succes_bonus;
    success_bonus += info->equipment.belt.crit_attack_succes_bonus;
    return (success_bonus);
}
