#include "dnd_tools.h"

void	ft_check_air_totem()
{
	t_char	*air_totem;
	int		error;

	air_totem = (t_char *)malloc(sizeof(t_char));
	if (!air_totem)
		return ;
	*air_totem = AIR_TOTEM_INFO;
	error = ft_npc_open_file(air_totem);
	if (error)
		return ;
	error = ft_npc_check_info(air_totem);
	if (error)
		return ;
	if (air_totem->stats.health > 0)
		ft_printf("there is an active air totem annyone within %i ft. is pushed back %i ft.\n",
			20, 20);
	return ;
}

void	ft_zephyr_turn(t_char *info)
{
	ft_update_buf(info);
	ft_check_air_totem();
	ft_zephyr_spells(info);
	ft_printf("Zephyr currently has %i/%i hp\n",
		info->stats.health, info->dstats.health);
}

void	ft_zephyr_ranged_attack(t_char *info)
{
	int	mod;
	int	dex_mod;
	int	result;
	int	damage;

	dex_mod = (info->stats.dex - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("Zephyr attacks with his bow and ");
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("rolled a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_printf("rolled a crit (%i)\n", result);
		damage = ft_dice_roll(2, 6) + dex_mod;
		ft_printf("Zephyr deals %i piercing damage\n", damage);
	}
	else
	{
		ft_printf("rolled %i+%i+%i+%i for a total of %i\n",
			result, dex_mod, info->attack_bonus.attack_bonus, mod, result
			+ dex_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(1, 6) + dex_mod;
		ft_printf("Zephyr deals %i piercing damage\n", damage);
	}
	return ;
}

void	ft_zephyr_attack(t_char *info)
{
	int	mod;
	int	dex_mod;
	int	result;
	int	damage;

	dex_mod = (info->stats.dex - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("Zephyr attacks with his sword and rolled ");
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_printf("a crit (%i)\n", result);
		damage = ft_dice_roll(2, 6) + dex_mod;
		ft_printf("Zephyr deals %i slashing damage\n", damage);
	}
	else
	{
		ft_printf("%i+%i+%i+%i for a total of %i\n",
			result, dex_mod, info->attack_bonus.attack_bonus, mod, result
			+ dex_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(1, 6) + dex_mod;
		ft_printf("Zephyr deals %i slashing damage\n", damage);
	}
	return ;
}

t_char	*ft_zephyr(int index, char **input, int exception)
{
	t_char	*info;

	info = (t_char *)malloc(sizeof(t_char));
	if (!info)
		return (NULL);
	*info = ZEPHYR_INFO;
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	free(info);
	return (NULL);
}
