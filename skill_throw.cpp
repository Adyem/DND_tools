#include "libft/Printf/printf.hpp"
#include "libft/RNG/RNG.hpp"
#include "dnd_tools.hpp"

void ft_skill_throw(t_char * info, const char *skill, int ability_mod, int skill_mod)
{
	int mod = 0;
	int result = 0;
	int roll = 0;

	roll = ft_dice_roll(1, 20);
	mod = ft_skill_check_buff(info, &result, skill);
	if (roll <= 1 + info->crit.skill_fail)
		pf_printf("%s rolled a critical fail (%d) on his/her %s\n", info->name, roll, skill);
	else if (roll >= 20 - info->crit.skill)
		pf_printf("%s rolled a crit (%d) on his/her %s\n", info->name, roll, skill);
	else
	{
		result = roll + (((ability_mod - 10) / 2) + skill_mod + mod);
		pf_printf("%s rolled %d+%d+%d+%d on his/her %s for a total of %d\n", info->name, roll, 
		          (ability_mod - 10) / 2, skill_mod, mod, skill, result);
	}
	return ;
}
