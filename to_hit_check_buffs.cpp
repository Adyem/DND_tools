#include "dnd_tools.hpp"
#include <iostream>

static void ft_to_hit_check_buff_chaos_armor()
{
	int effect_roll;
	int damage_roll;

	effect_roll = ft_dice_roll(1, 6);
	if (effect_roll == 1)
	{
		damage_roll = ft_dice_roll(2, 6);
		std::cout << "Chaos Armor activates: The attacker takes " << damage_roll 
		          << " fire damage!" << std::endl;
	}
	else if (effect_roll == 2)
	{
		damage_roll = ft_dice_roll(1, 6) + 2;
		std::cout << "Chaos Armor activates: The attacker takes " << damage_roll 
		          << " ice damage and is slowed, halving his/her movement!" << std::endl;
	}
	else if (effect_roll == 3)
	{
		damage_roll = ft_dice_roll(1, 8);
		std::cout << "Chaos Armor activates: The attacker takes " << damage_roll 
		          << " lightning damage and is stunned!" << std::endl;
	}
	else if (effect_roll == 4)
	{
		damage_roll = ft_dice_roll(2, 4);
		std::cout << "Chaos Armor activates: The attacker takes " << damage_roll 
		          << " poison damage and is poisoned, he/she now has disadvantage on " 
		          << "attack rolls and ability checks" << std::endl;
	}
	else if (effect_roll == 5 || effect_roll == 6)
		std::cout << "Chaos Armor activates: But nothing happens..." << std::endl;
}

void ft_to_hit_check_buff(t_char *info)
{
	if ((info->bufs.chaos_armor.duration) > 0)
		ft_to_hit_check_buff_chaos_armor();
	return ;
}
