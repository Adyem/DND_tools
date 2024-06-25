#include "dnd_tools.h"

void	ft_template_turn(t_char *info)
{
	ft_update_buf(info);
	ft_printf("The template will try to make either a ranged or melee attack during his turn\n");
	ft_printf("Template currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
}

void	ft_template_ranged_attack(t_char *info)
{
	int	mod;
	int	dex_mod;
	int	result;
	int	damage;

	dex_mod = (info->stats.dex - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("%s attacks with his bow and ", info->name);
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

void	ft_template_attack(t_char *info)
{
	int	mod;
	int	dex_mod;
	int	result;
	int	damage;

	dex_mod = (info->stats.dex - 10) / 2;
	result = ft_dice_roll(1, 20);
	mod = ft_attack_roll_check_buffs(info, &result);
	ft_printf("%s attacks with his sword and rolled ", info->name);
	if (result <= 1 + info->crit.attack_fail)
		ft_printf("a critical fail (%i) and missed on his attack\n",
			result);
	else if (result >= 20 - info->crit.attack)
	{
		ft_check_buff_damage(info);
		ft_printf("a crit (%i) and ", result);
		damage = ft_dice_roll(2, 6) + dex_mod;
		ft_printf("deals %i piercing damage\n", damage);
	}
	else
	{
		ft_check_buff_damage(info);
		ft_printf("%i+%i+%i+%i for a total of %i and ",
			result, dex_mod, info->attack_bonus.attack_bonus, mod, result
			+ dex_mod + mod + info->attack_bonus.attack_bonus);
		damage = ft_dice_roll(1, 6) + dex_mod;
		ft_printf("deals %i piercing damage\n", damage);
	}
	return ;
}

t_char	*ft_template(int index, char **input, t_name *name, int exception)
{
	t_char	*info;

	info = (t_char *)calloc(1, sizeof(t_char));
	if (!info)
		return (NULL);
	*info = TEMPLATE_INFO;
	info->name = input[0];
	info->struct_name = name;
	info->save_file = ft_strjoin("data/", input[0]);
	if (!info->save_file)
		return (NULL);
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (NULL);
}
