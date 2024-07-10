#include "dnd_tools.h"

static void	ft_npc_update_hp(t_char *info, const char **input)
{
	int	number;
	int	temp;

	if (ft_check_value(input[2]))
	{
		ft_printf_fd(2, "Expecting a positive or negative integer\n");
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

void	ft_npc_set_stat(t_char *info, const char **input)
{
	if (ft_strcmp_dnd(input[2], "flank") == 0 || ft_strcmp_dnd(input[2], "flanking"))
	{
		info->flags.flanking = 1;
		if (ft_strcmp_dnd(input[1], "attack") == 0)
		{
			if (info->equipment.weapon.attack.function)
				info->equipment.weapon.attack.function(info, &info->equipment.weapon);
			else
				ft_printf_fd(2, "No attack for %s set\n", info->name);
		}
		else if (ft_strcmp_dnd(input[1], "ranged_attack") == 0)
		{
			if (info->equipment.ranged_weapon.attack.function)
				info->equipment.ranged_weapon.attack.function(info, &info->equipment.ranged_weapon);
			else
				ft_printf_fd(2, "No ranged attack for %s set\n", info->name);
		}
		else
			ft_printf_fd(2, "6-Error invalid argument given\n");
	}
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
			ft_saving_throw(info, "strength", ft_calculate_str(info), info->save_mod.str);
		else if (ft_strcmp_dnd(input[1], "dex") == 0)
			ft_saving_throw(info, "dexterity", ft_calculate_dex(info), info->save_mod.dex);
		else if (ft_strcmp_dnd(input[1], "con") == 0)
			ft_saving_throw(info, "constituion", ft_calculate_con(info), info->save_mod.con);
		else if (ft_strcmp_dnd(input[1], "int") == 0)
			ft_saving_throw(info, "intelligence", ft_calculate_inte(info), info->save_mod.inte);
		else if (ft_strcmp_dnd(input[1], "wis") == 0)
			ft_saving_throw(info, "wisdom", ft_calculate_wis(info), info->save_mod.wis);
		else if (ft_strcmp_dnd(input[1], "cha") == 0)
			ft_saving_throw(info, "charisma", ft_calculate_cha(info), info->save_mod.cha);
		else
		{
			ft_printf_fd(2, "4-%s Invalid argument given\n", info->name);
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
		ft_printf_fd(2, "5-%s Invalid argument given\n", info->name);
		return ;
	}
	return ;
}
