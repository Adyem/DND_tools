#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/shared_ptr.hpp"

void ft_weapon_attack(ft_sharedptr<t_char> &info, t_equipment_id *weapon, int offhand)
{
    t_damage_info d_info;
    d_info.stat_mod = (ft_weapon_find_stat(info, weapon) - 10) / 2;
    d_info.result = ft_dice_roll(1, 20);
    if (d_info.result == -1)
    {
        pf_printf_fd(2, "101-Error: dice rolling error in attack\n");
        return ;
    }
    pf_printf("%s attacks with his/her %s and rolled a %d on the die.\n",
              info->name, weapon->name, d_info.result);
    if (d_info.result <= 1 + info->crit.attack_fail)
        pf_printf("A critical fail (%d)! That can't be good...\n", d_info.result);
    bool is_hit = false;
	if (d_info.result >= 20 - info->crit.attack)
	{
		is_hit = true;
		pf_printf("%s critical hit (%d)!\n", info->name, d_info.result);
	}
	else if (d_info.result <= 1 + info->crit.attack_fail)
		pf_printf("%s Rolled a critical fail (%d)!\n", info->name, d_info.result);
	else if (g_dnd_test == true)
    {
        int test_roll = ft_dice_roll(1, 2);
        if (test_roll == 1)
            is_hit = true;
        else
            is_hit = false;
        if (is_hit)
            pf_printf("[TEST MODE] The attack is a HIT (random)!\n");
        else
        {
            pf_printf("[TEST MODE] The attack is a MISS (random)!\n");
            return ;
        }
    }
	else
    {
        int choice = ft_readline_prompt_hit_or_miss();
        if (choice == -1)
            return ;
        else if (choice == 2)
        {
            pf_printf("Exiting attack...\n");
            return ;
        }
        else if (choice == 1)
        {
            pf_printf("%s missed the attack.\n", info->name);
            return ;
        }
        else
            is_hit = true;
    }
    bool is_crit = false;
    ft_check_dice_amount_and_faces(weapon, &d_info, offhand, info);
    ft_calculate_damage(weapon, &d_info, is_crit);
    if (is_hit)
        ft_prompt_on_attack_success(info, is_crit);
    return ;
}
