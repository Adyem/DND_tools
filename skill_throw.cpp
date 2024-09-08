#include "dnd_tools.hpp"
#include <iostream>

void ft_skill_throw(t_char *info, const char *skill, int ability_mod, int skill_mod)
{
	int mod;
	int result;
	int roll;

	roll = ft_dice_roll(1, 20);
	mod = ft_skill_check_buff(info, &result, skill);
	if (roll <= 1 + info->crit.skill_fail)
		std::cout << info->name << " rolled a critical fail (" << roll 
		          << ") on his/her " << skill << "\n";
	else if (roll >= 20 - info->crit.skill)
		std::cout << info->name << " rolled a crit (" << roll 
		          << ") on his/her " << skill << "\n";
	else
	{
		result = roll + (((ability_mod - 10) / 2) + skill_mod + mod);
		std::cout << info->name << " rolled " << roll << "+" << (ability_mod - 10) / 2 << "+" 
		          << skill_mod << "+" << mod << " on his/her " << skill 
		          << " for a total of " << result << "\n";
	}
	return ;
}
