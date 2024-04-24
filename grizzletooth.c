#include "dnd_tools.h"

void	ft_grizzletooth_turn(t_char *info)
{
	ft_update_buf(info);
	ft_printf("The grizzletooth will try to make either a ranged or melee attack during his turn\n");
	ft_printf("If on low health the air grizzletooth will try to use nimble escape: %s",
		GRIZZLETOOTH_NIMBLE_ESCAPE);
	ft_printf("Grizzletooth currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
}

void	ft_grizzletooth_ranged_attack(t_char *info)
{
	int	mod;
	int	dex_mod;
	int	result;
	int	damage;

	dex_mod = (info->stats.dex - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("Grizzletooth attacks with his bow and ");
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("rolled a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_printf("rolled a crit (%i)\n", result);
		damage = ft_dice_roll(2, 6) + dex_mod;
		ft_printf("Grizzletooth deals %i piercing damage\n", damage);
	}
	else
	{
		ft_printf("rolled %i+%i+%i+%i for a total of %i\n",
			result, dex_mod, info->attack_bonus.attack_bonus, mod, result
			+ dex_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(1, 6) + dex_mod;
		ft_printf("Grizzletooth deals %i piercing damage\n", damage);
	}
	return ;
}

void	ft_grizzletooth_attack(t_char *info)
{
	int	mod;
	int	dex_mod;
	int	result;
	int	damage;

	dex_mod = (info->stats.dex - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("Grizzletooth attacks with his sword and rolled ");
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_printf("a crit (%i)\n", result);
		damage = ft_dice_roll(2, 6) + dex_mod;
		ft_printf("Grizzletooth deals %i slashing damage\n", damage);
	}
	else
	{
		ft_printf("%i+%i+%i+%i for a total of %i\n",
			result, dex_mod, info->attack_bonus.attack_bonus, mod, result
			+ dex_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(1, 6) + dex_mod;
		ft_printf("Grizzletooth deals %i slashing damage\n", damage);
	}
	return ;
}

t_char	*ft_grizzletooth(int index, char **input, int exception)
{
	char	*temp;
	t_char	*info;

	info = (t_char *)malloc(sizeof(t_char));
	if (!info)
		return (NULL);
	*info = GRIZZLETOOTH_INFO;
	if (exception)
		return (info);
	temp = ft_strjoin(input[0], ".txt");
	if (!temp)
		return (NULL);
	info->save_file = ft_strjoin("data/", temp);
	free (temp);
	if (!info->save_file)
		return (NULL);
	ft_npc_change_stats(info, index, input);
	free(info->save_file);
	free(info);
	return (NULL);
}
