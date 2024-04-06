#include "dnd_tools.h"

static void	ft_npc_update_hp(t_char *info, char **input)
{
	int	number;
	int	temp;

	if (ft_check_value(input[2]))
	{
		ft_printf_fd(2, "Expecting a positive or negative integer");
		return ;
	}
	number = ft_atoi(input[2]);
	temp = info->stats.health;
	info->stats.health = info->stats.health + number;
	if (info->stats.health > info->dstats.health)
		info->stats.health = info->dstats.health;
	else if (info->stats.health < 0)
			info->stats.health = 0;
	ft_print_character_status(info, number, temp);
	return ;
}

void	ft_npc_set_stat(t_char *info, char **input)
{
	if (DEBUG == 1)
		ft_printf("npc_set_stat\n");
	else if (ft_strcmp_dnd(input[1], "hp") == 0)
		ft_npc_update_hp(info, input);
	else if (ft_strcmp_dnd(input[1], "bless") == 0)
		ft_npc_update_buff(info, input, &info->bufs.bless.duration, "bless");
	else if (ft_strcmp_dnd(input[1], "lightning_strike") == 0)
		ft_npc_update_lightning_strike(info, input);
	else if (ft_strcmp_dnd(input[1], "protective_winds") == 0)
		ft_npc_update_buff(info, input,
			&info->bufs.protective_winds.duration, "protective winds");
	else if (ft_strcmp_dnd(input[1], "to_hit") == 0)
		ft_npc_check_ac(info, input);
	else if (ft_strcmp_dnd(input[2], "save") == 0)
	{
		if (ft_strcmp_dnd(input[1], "str") == 0)
			ft_saving_throw(info, "strength", info->stats.str, info->save_mod.str);
		else if (ft_strcmp_dnd(input[1], "dex") == 0)
			ft_saving_throw(info, "dexterity", info->stats.dex, info->save_mod.dex);
		else if (ft_strcmp_dnd(input[1], "con") == 0)
			ft_saving_throw(info, "constituion", info->stats.con, info->save_mod.con);
		else if (ft_strcmp_dnd(input[1], "int") == 0)
			ft_saving_throw(info, "intelligence", info->stats.inte, info->save_mod.inte);
		else if (ft_strcmp_dnd(input[1], "wis") == 0)
			ft_saving_throw(info, "wisdom", info->stats.wis, info->save_mod.wis);
		else if (ft_strcmp_dnd(input[1], "cha") == 0)
			ft_saving_throw(info, "charisma", info->stats.cha, info->save_mod.cha);
		else
		{
			ft_printf_fd(2, "4-Maverick Invalid argument given\n");
			return ;
		}
	}
	else if (ft_strcmp_dnd(input[1], "initiative") == 0)
	{
		if (ft_strcmp_dnd(input[2] , "roll") == 0)
			ft_roll_initiative(info);
		else
		{
			ft_printf("3-%s invalid commannd", info->name);
			return ;
		}
	}
	else
	{
		ft_printf_fd(2, "4-%s Invalid argument given\n", info->name);
		return ;
	}
	return ;
}
