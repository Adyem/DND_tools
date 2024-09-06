#include "dnd_tools.h"

void	ft_skill_throw(t_char *info, const char *skill, int ability_mod, int skill_mod)
{
	int mod;
	int	result;
	int	roll;

	roll = ft_dice_roll(1, 20);
	mod = ft_skill_check_buff(info, &result, skill);
	if (roll <= 1 + info->crit.skill_fail)
		ft_printf("%s rolled a critical fail (%i) on his/her %s\n",
			info->name, roll, skill);
	else if (roll >= 20 - info->crit.skill)
		ft_printf("%s rolled a crit (%i) on his/her %s\n",
			info->name, roll, skill);
	else
	{
		result = roll + (((ability_mod - 10) / 2) + skill_mod + mod);
		ft_printf("%s rolled %i+%i+%i+%i on his/her %s for a total of %i\n",
			info->name, roll, (ability_mod - 10) / 2, skill_mod, mod, skill, result);
	}
	return ;
}
