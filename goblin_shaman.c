#include "dnd_tools.h"

void	ft_goblin_shaman_turn(t_char *info)
{
	ft_update_buf(info);
	ft_printf("The goblin_shaman_shaman will try to make either a ranged or melee attack during his turn\n");
	ft_printf("If on low health the air goblin_shaman_shaman will try to use nimble escape: %s\n",
		GOBLIN_SHAMAN_NIMBLE_ESCAPE);
	ft_printf("The goblin_shaman_shaman currently has %i/%i hp\n",
		info->stats.health, info->dstats.health);
}

void	ft_goblin_shaman_ranged_attack(t_char *info)
{
	int	mod;
	int	int_mod;
	int	result;
	int	damage;

	int_mod = (info->stats.inte - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("Goblin_shaman_shaman attacks throwing a bolt fire ");
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("rolled a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_printf("rolled a crit (%i)\n", result);
		damage = ft_dice_roll(2, 6) + int_mod;
		ft_printf("Goblin_shaman_shaman deals %i fire damage\n", damage);
	}
	else
	{
		ft_printf("rolled %i+%i+%i+%i for a total of %i\n",
			result, int_mod, info->attack_bonus.attack_bonus, mod, result
			+ int_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(1, 6) + int_mod;
		ft_printf("Goblin_shaman_shaman deals %i fire damage\n", damage);
	}
	return ;
}

void	ft_goblin_shaman_attack(t_char *info)
{
	int	mod;
	int	str_mod;
	int	result;
	int	damage;

	str_mod = (info->stats.str - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("Goblin_shaman_shaman attacks with his staff and rolled ");
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_printf("a crit (%i)\n", result);
		damage = ft_dice_roll(2, 6) + str_mod;
		ft_printf("Goblin_shaman_shaman deals %i bludgeoning damage\n", damage);
	}
	else
	{
		ft_printf("%i+%i+%i+%i for a total of %i\n",
			result, str_mod, info->attack_bonus.attack_bonus, mod, result
			+ str_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(1, 6) + str_mod;
		ft_printf("Goblin_shaman_shaman deals %i bludgeoning damage\n", damage);
	}
	return ;
}

t_char	*ft_goblin_shaman(int index, char **input, t_name *name, int exception)
{
	char	*temp;
	t_char	*info;

	info = (t_char *)malloc(sizeof(t_char));
	if (!info)
		return (NULL);
	*info = GOBLIN_SHAMAN_INFO;
	info->struct_name = name;
	if (exception)
		return (info);
	temp = ft_strjoin(input[0], ".txt");
	if (!temp)
		return (NULL);
	info->save_file = ft_strjoin("data/", temp);
	free (temp);
	if (!info->save_file)
		return (NULL);
	info->name = input[0];
	ft_npc_change_stats(info, index, input);
	free(info->save_file);
	free(info);
	return (NULL);
}
