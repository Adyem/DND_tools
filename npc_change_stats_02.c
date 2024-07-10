#include "dnd_tools.h"

void	ft_npc_sstuff(t_char *info, const char **input)
{
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
	else if (ft_strcmp_dnd(input[1], "kill") == 0)
		ft_kill(info);
	else if (ft_strcmp_dnd(input[1], "damage") == 0)
		ft_request_damage(info);
	else if (ft_strcmp_dnd(input[1], "hp") == 0)
		ft_print_character_status(info, 0, info->stats.health);
	else if (ft_strcmp_dnd(input[1], "athletics") == 0)
		ft_skill_throw(info, "athletics", ft_calculate_str(info), info->skill_mod.athletics);
	else if (ft_strcmp_dnd(input[1], "acrobatics") == 0)
		ft_skill_throw(info, "acrobatics", ft_calculate_dex(info), info->skill_mod.acrobatics);
	else if (ft_strcmp_dnd(input[1], "sleight_of_hand") == 0)
		ft_skill_throw(info, "sleight_of_hand",
			ft_calculate_dex(info), info->skill_mod.sleight_of_hand);
	else if (ft_strcmp_dnd(input[1], "stealth") == 0)
		ft_skill_throw(info, "stealth", ft_calculate_dex(info), info->skill_mod.stealth);
	else if (ft_strcmp_dnd(input[1], "arcana") == 0)
		ft_skill_throw(info, "arcana", ft_calculate_inte(info), info->skill_mod.arcana);
	else if (ft_strcmp_dnd(input[1], "history") == 0)
		ft_skill_throw(info, "history", ft_calculate_inte(info), info->skill_mod.history);
	else if (ft_strcmp_dnd(input[1], "investigation") == 0)
		ft_skill_throw(info, "investigation",
			ft_calculate_inte(info), info->skill_mod.investigation);
	else if (ft_strcmp_dnd(input[1], "nature") == 0)
		ft_skill_throw(info, "nature", ft_calculate_inte(info), info->skill_mod.nature);
	else if (ft_strcmp_dnd(input[1], "religion") == 0)
		ft_skill_throw(info, "religion", ft_calculate_inte(info), info->skill_mod.religion);
	else if (ft_strcmp_dnd(input[1], "animal_handling") == 0)
		ft_skill_throw(info, "animal_handling",
			ft_calculate_wis(info), info->skill_mod.animal_handling);
	else if (ft_strcmp_dnd(input[1], "insight") == 0)
		ft_skill_throw(info, "insight", ft_calculate_wis(info), info->skill_mod.insight);
	else if (ft_strcmp_dnd(input[1], "medicine") == 0)
		ft_skill_throw(info, "medicine", ft_calculate_wis(info), info->skill_mod.medicine);
	else if (ft_strcmp_dnd(input[1], "perception") == 0)
		ft_skill_throw(info, "perception", ft_calculate_wis(info), info->skill_mod.perception);
	else if (ft_strcmp_dnd(input[1], "survival") == 0)
		ft_skill_throw(info, "survival", ft_calculate_wis(info), info->skill_mod.survival);
	else if (ft_strcmp_dnd(input[1], "deception") == 0)
		ft_skill_throw(info, "deception", ft_calculate_cha(info), info->skill_mod.deception);
	else if (ft_strcmp_dnd(input[1], "intimidation") == 0)
		ft_skill_throw(info, "intimidation", ft_calculate_cha(info), info->skill_mod.intimidation);
	else if (ft_strcmp_dnd(input[1], "performance") == 0)
		ft_skill_throw(info, "performance", ft_calculate_cha(info), info->skill_mod.performance);
	else if (ft_strcmp_dnd(input[1], "persuasion") == 0)
		ft_skill_throw(info, "persuasion", ft_calculate_cha(info), info->skill_mod.persuasion);
	else if (ft_strcmp_dnd(input[1], "initiative") == 0)
		ft_check_initiative(info);
	else 
		ft_printf("4-Invalid command given\n");
	return ;
}

