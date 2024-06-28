#include "dnd_tools.h"

void	ft_wooden_bow_attack(t_char *info)
{
	int	mod;
	int	dex_mod;
	int	result;
	int	damage;

	dex_mod = (info->stats.dex - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("%s attacks with his\\her wooden bow and ", info->name);
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("rolled a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_printf("rolled a crit (%i) and ", result);
		damage = ft_dice_roll(2, 6) + dex_mod;
		ft_printf("deals %i piercing damage\n", damage);
	}
	else
	{
		ft_printf("rolled %i+%i+%i+%i for a total of %i and ",
			result, dex_mod, info->attack_bonus.attack_bonus, mod, result
			+ dex_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(1, 6) + dex_mod;
		ft_printf("deals %i piercing damage\n", damage);
	}
	return ;
}
