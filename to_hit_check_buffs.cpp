#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

static void ft_to_hit_check_buff_chaos_armor()
{
	int effect_roll;
	int damage_roll;

	effect_roll = ft_dice_roll(1, 6);
	if (effect_roll == 1)
	{
		damage_roll = ft_dice_roll(2, 6);
		pf_printf("Chaos Armor activates: The attacker takes %d fire damage!\n", damage_roll);
	}
	else if (effect_roll == 2)
	{
		damage_roll = ft_dice_roll(1, 6) + 2;
		pf_printf("Chaos Armor activates: The attacker takes %d ice damage and is slowed, " \
				"halving his/her movement!\n", damage_roll);
	}
	else if (effect_roll == 3)
	{
		damage_roll = ft_dice_roll(1, 8);
		pf_printf("Chaos Armor activates: The attacker takes %d lightning damage and is stunned!\n", damage_roll);
	}
	else if (effect_roll == 4)
	{
		damage_roll = ft_dice_roll(2, 4);
		pf_printf("Chaos Armor activates: The attacker takes %d poison damage and is poisoned, " \
				"he/she now has disadvantage on attack rolls and ability checks\n", damage_roll);
	}
	else if (effect_roll == 5 || effect_roll == 6)
		pf_printf("Chaos Armor activates: But nothing happens...\n");
}

void ft_to_hit_check_buff(ft_sharedptr<t_char> &info)
{
	if ((info->bufs.chaos_armor.duration) > 0)
		ft_to_hit_check_buff_chaos_armor();
	return ;
}
