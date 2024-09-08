#include "dnd_tools.hpp"
#include <iostream>

int ft_saving_throw(t_char *info, const char *ability_score, int ability_mod, int save_mod)
{
	int mod;
	int result;
	int roll;

	roll = ft_dice_roll(1, 20);
	mod = ft_save_check_buff(info, &roll, ability_score);
	if (roll <= 1 + info->crit.save_fail)
		result = CRIT_FAIL, std::cout << info->name << " rolled a critical fail (" << roll 
                                      << ") on his/her " << ability_score << " saving throw\n";
	else if (roll >= 20 - info->crit.save)
		result = CRIT_SUCCES, std::cout << info->name << " rolled a crit (" << roll 
                                        << ") on his/her " << ability_score 
                                        << " saving throw\n";
	else
	{
		result = roll + (((ability_mod - 10) / 2) + save_mod + mod);
		std::cout << info->name << " rolled " << roll << "+" << (ability_mod - 10) / 2 << "+" 
                  << save_mod << "+" << mod << " on his/her " << ability_score 
                  << " saving throw for a total of " << result << "\n";
	}
	return (result);
}
