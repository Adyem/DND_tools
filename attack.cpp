#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/shared_ptr.hpp"

static void	ft_test_mode(bool *is_hit)
{
	int test_roll = ft_dice_roll(1, 2);
	if (test_roll == 1)
		*is_hit = true;
	else
		*is_hit = false;
	return ;
}

static void ft_normal_mode(ft_sharedptr<t_char> &info, bool *is_hit)
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
		*is_hit = true;
	return ;
}

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
    if (d_info.result <= 1 + ft_calculate_crit_attack_fail_bonus(info))
        pf_printf("A critical fail (%d)! That can't be good...\n", d_info.result);
    bool is_hit = false;
	if (d_info.result >= 20 - info->crit.attack)
	{
		is_hit = true;
		pf_printf("%s critical hit (%d)!\n", info->name, d_info.result);
	}
	else if (d_info.result <= 1 + ft_calculate_crit_attack_success_bonus(info))
		pf_printf("%s Rolled a critical fail (%d)!\n", info->name, d_info.result);
	else if (g_dnd_test == true)
		ft_test_mode(&is_hit);
	else
		ft_normal_mode(info, &is_hit);
	bool is_crit = false;
    ft_check_dice_amount_and_faces(weapon, &d_info, offhand, info);
	if (is_hit)
	{
    	ft_calculate_damage(weapon, &d_info, is_crit);
        ft_prompt_on_attack_success(info, is_crit);
	}
    return ;
}
