#include "dnd_tools.h"

void	ft_maverick_turn(t_char *info)
{
	int		first;
	int		second;

	ft_update_buf(info);
	first = 0;
	second = 0;
	while (first == second)
	{
		first = ft_dice_roll(1, 8);
		second = ft_dice_roll(1, 8);
	}
	ft_maverick_print_f(first, second);
	ft_maverick_print_s(first, second);
}

void	ft_maverick_attack(t_char *info)
{
	int	mod;
	int	dex_mod;
	int	result;
	int	damage;

	dex_mod = (info->stats.dex - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("Maverick attacks with his claws and rolled ");
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_printf("a crit (%i)\n", result);
		damage = ft_dice_roll(2, 6) + dex_mod;
		ft_printf("Maverick deals %i piercing damage\n", damage);
	}
	else
	{
		ft_printf("%i+%i+%i+%i for a total of %i\n",
			result, dex_mod, info->attack_bonus.attack_bonus, mod, result
			+ dex_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(1, 6) + dex_mod;
		ft_printf("Maverick deals %i piercing damage\n", damage);
	}
	return ;
}

void	ft_maverick(int index, char **input, int exception)
{
	t_char	*info;

	info = (t_char *)malloc(sizeof(t_char));
	if (!info)
		return ;
	*info = MAVERICK_INFO;
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	free(info);
	return (NULL);
}
