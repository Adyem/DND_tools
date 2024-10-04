#include "dnd_tools.hpp"
#include "libft/Printf/ft_printf.hpp"

static int	ft_skill_roll(t_char *info, const char **input)
{
	if (ft_strcmp_dnd(input[1], "athletics") == 0)
		ft_skill_throw(info, "athletics", ft_calculate_str(info), ft_calculate_athletics(info));
	else if (ft_strcmp_dnd(input[1], "acrobatics") == 0)
		ft_skill_throw(info, "acrobatics", ft_calculate_dex(info), ft_calculate_acrobatics(info));
	else if (ft_strcmp_dnd(input[1], "sleight_of_hand") == 0)
		ft_skill_throw(info, "sleight_of_hand", ft_calculate_dex(info), ft_calculate_sleight_of_hand(info));
	else if (ft_strcmp_dnd(input[1], "stealth") == 0)
		ft_skill_throw(info, "stealth", ft_calculate_dex(info), ft_calculate_stealth(info));
	else if (ft_strcmp_dnd(input[1], "arcana") == 0)
		ft_skill_throw(info, "arcana", ft_calculate_inte(info), ft_calculate_arcana(info));
	else if (ft_strcmp_dnd(input[1], "history") == 0)
		ft_skill_throw(info, "history", ft_calculate_inte(info), ft_calculate_history(info));
	else if (ft_strcmp_dnd(input[1], "investigation") == 0)
		ft_skill_throw(info, "investigation", ft_calculate_inte(info), ft_calculate_investigation(info));
	else if (ft_strcmp_dnd(input[1], "nature") == 0)
		ft_skill_throw(info, "nature", ft_calculate_inte(info), ft_calculate_nature(info));
	else if (ft_strcmp_dnd(input[1], "religion") == 0)
		ft_skill_throw(info, "religion", ft_calculate_inte(info), ft_calculate_religion(info));
	else if (ft_strcmp_dnd(input[1], "animal_handling") == 0)
		ft_skill_throw(info, "animal_handling", ft_calculate_wis(info), ft_calculate_animal_handling(info));
	else if (ft_strcmp_dnd(input[1], "insight") == 0)
		ft_skill_throw(info, "insight", ft_calculate_wis(info), ft_calculate_insight(info));
	else if (ft_strcmp_dnd(input[1], "medicine") == 0)
		ft_skill_throw(info, "medicine", ft_calculate_wis(info), ft_calculate_medicine(info));
	else if (ft_strcmp_dnd(input[1], "perception") == 0)
		ft_skill_throw(info, "perception", ft_calculate_wis(info), ft_calculate_perception(info));
	else if (ft_strcmp_dnd(input[1], "survival") == 0)
		ft_skill_throw(info, "survival", ft_calculate_wis(info), ft_calculate_survival(info));
	else if (ft_strcmp_dnd(input[1], "deception") == 0)
		ft_skill_throw(info, "deception", ft_calculate_cha(info), ft_calculate_deception(info));
	else if (ft_strcmp_dnd(input[1], "intimidation") == 0)
		ft_skill_throw(info, "intimidation", ft_calculate_cha(info), ft_calculate_intimidation(info));
	else if (ft_strcmp_dnd(input[1], "performance") == 0)
		ft_skill_throw(info, "performance", ft_calculate_cha(info), ft_calculate_performance(info));
	else if (ft_strcmp_dnd(input[1], "persuasion") == 0)
		ft_skill_throw(info, "persuasion", ft_calculate_cha(info), ft_calculate_persuasion(info));
	else
		return (1);
	return (0);
}	

void	ft_npc_sstuff(t_char *info, const char **input)
{
	if (ft_strcmp_dnd(input[1], "attack") == 0)
	{
		if (info->equipment.weapon.attack.function)
			info->equipment.weapon.attack.function(info, &info->equipment.weapon, 0);
		else
			ft_printf_fd(2, "no weapon attack set for %s\n", info->name);
	}
	else if (ft_strcmp_dnd(input[1], "ranged_attack") == 0)
	{
		if (info->equipment.ranged_weapon.attack.function)
			info->equipment.ranged_weapon.attack.function(info, &info->equipment.ranged_weapon, 0);
		else
			ft_printf_fd(2, "no ranged weapon attack set for %s\n", info->name);
	}
	else if (ft_strcmp_dnd(input[1], "prone") == 0)
		info->flags.prone = 1;
	else if (ft_strcmp_dnd(input[1], "kill") == 0)
		ft_kill(info);
	else if (ft_strcmp_dnd(input[1], "damage") == 0)
		ft_request_damage(info);
	else if (ft_strcmp_dnd(input[1], "hp") == 0)
		ft_printf("HP: %d\n", info->stats.health);
	else if (ft_strcmp_dnd(input[1], "initiative") == 0)
		ft_check_initiative(info);
	else if (ft_skill_roll(info, input) == 0)
		return ;
	else
		ft_printf_fd(2, "4-Invalid command given\n");
	return ;
}
