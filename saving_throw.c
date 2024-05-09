#include "dnd_tools.h"

int	ft_saving_throw(t_char *info, char *ability_score, int ability_mod, int save_mod)
{
	int mod;
	int	result;
	int	roll;

	roll = ft_dice_roll(1, 20);
	mod = ft_save_check_buff(info, &roll, ability_score);
	if (roll <= 1 + info->crit.save_fail)
	{
		result = CRIT_FAIL;
		ft_printf("%s rolled a critical fail (%i) on his/her %s saving throw\n",
			info->name, roll, ability_score);
	}
	else if (roll >= 20 - info->crit.save)
	{
		result = CRIT_SUCCES;
		ft_printf("%s rolled a crit (%i) on his/her %s saving throw\n",
			info->name, roll, ability_score);
	}
	else
	{
		result = roll + (((ability_mod - 10) / 2) + save_mod + mod);
		ft_printf("%s rolled %i+%i+%i+%i on his/her %s saving throw for a total of %i\n",
			info->name, roll, (ability_mod - 10) / 2, save_mod, mod, ability_score, result);
	}
	return (result);
}

