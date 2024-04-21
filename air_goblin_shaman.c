#include "dnd_tools.h"

void	ft_air_goblin_shaman_turn(t_char *info)
{
	ft_update_buf(info);
	ft_printf("The goblin will try to make either a" \
			" ranged or melee attack during his turn\n\n");
	ft_printf("If on low health the air goblin will try to use nimble escape: %s\n\n",
		AIR_GOBLIN_SHAMAN_NIMBLE_ESCAPE);
	ft_printf("The goblin currently has %i/%i hp\n",
		info->stats.health, info->dstats.health);
}

void	ft_air_goblin_shaman_ranged_attack(t_char *info)
{
	int	mod;
	int	stat_mod;
	int	result;
	int	damage;

	stat_mod = (info->stats.inte - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("Air_goblin_shaman attacks using a bolt of lightning and rolled ");
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_printf("a crit (%i)\n", result);
		damage = ft_dice_roll(2, 8) + stat_mod;
		ft_printf("Air_goblin_shaman deals %i lightning damage\n", damage);
	}
	else
	{
		ft_printf("%i+%i+%i+%i for a total of %i\n",
			result, stat_mod, info->attack_bonus.attack_bonus, mod, result
			+ stat_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(1, 8) + stat_mod;
		ft_printf("Air_goblin_shaman deals %i lightning damage\n", damage);
	}
	return ;
}

void	ft_air_goblin_shaman_attack(t_char *info)
{
	int	mod;
	int	stat_mod;
	int	result;
	int	damage;

	stat_mod = (info->stats.str - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("Air_goblin_shaman attacks with his staff and rolled ");
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_printf("a crit (%i)\n", result);
		damage = ft_dice_roll(2, 6) + stat_mod;
		ft_printf("Air_goblin_shaman deals %i bludgeoning damage\n", damage);
	}
	else
	{
		ft_printf("%i+%i+%i+%i for a total of %i\n",
			result, stat_mod, info->attack_bonus.attack_bonus, mod, result
			+ stat_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(1, 6) + stat_mod;
		ft_printf("Air_goblin_shaman deals %i bludgeoning damage\n", damage);
	}
	return ;
}

void	ft_air_goblin_shaman(int index, char **input)
{
	char	*temp;
	t_char	*info;

	info = (t_char *)malloc(sizeof(t_char));
	if (!info)
		return ;
	*info = AIR_GOBLIN_SHAMAN_INFO;
	temp = ft_strjoin(input[0], ".txt");
	if (!temp)
		return ;
	info->save_file = ft_strjoin("data/", temp);
	free (temp);
	if (!info->save_file)
		return ;
	ft_npc_change_stats(info, index, input);
	free(info->save_file);
	free(info);
	return ;
}
