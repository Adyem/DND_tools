#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

int ft_saving_throw(SharedPtr<t_char> info, const char *ability_score, int ability_mod, int save_mod)
{
	int mod;
	int result;
	int roll;

	roll = ft_dice_roll(1, 20);
	mod = ft_save_check_buff(info, &roll, ability_score);
	if (roll <= 1 + info->crit.save_fail)
	{
		result = CRIT_FAIL;
		pf_printf("%s rolled a critical fail (%d) on his/her %s saving throw\n",
				info->name, roll, ability_score);
	}
	else if (roll >= 20 - info->crit.save)
	{
		result = CRIT_SUCCES;
		pf_printf("%s rolled a crit (%d) on his/her %s saving throw\n",
				info->name, roll, ability_score);
	}
	else
	{
		result = roll + (((ability_mod - 10) / 2) + save_mod + mod);
		pf_printf("%s rolled %d+%d+%d+%d on his/her %s saving throw for a total of %d\n",
			info->name, roll, (ability_mod - 10) / 2, save_mod, mod, ability_score, result);
	}
	return (result);
}
