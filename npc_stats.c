#include "dnd_tools.h"

static void	ft_npc_sstuff(t_char *info, char **input)
{
	if (ft_strcmp_dnd(input[1], "attack") == 0)
	{
		if (info->f_attack.attack)
			info->f_attack.attack(info);
		else
			ft_printf_fd(2, "No attack for %s set\n", info->name);
	}
	else if (ft_strcmp_dnd(input[1], "ranged_attack") == 0)
	{
		if (info->f_attack.ranged_attack)
			info->f_attack.ranged_attack(info);
		else
			ft_printf_fd(2, "No ranged attack for %s set\n", info->name);
	}
	else if (ft_strcmp_dnd(input[1], "hp") == 0)
		ft_print_character_status(info, 0, info->stats.health);
	else if (ft_strcmp_dnd(input[1], "athletics") == 0)
		ft_skill_throw(info, "athletics", info->stats.str, info->skill_mod.athletics);
	else if (ft_strcmp_dnd(input[1], "acrobatics") == 0)
		ft_skill_throw(info, "acrobatics", info->stats.dex, info->skill_mod.acrobatics);
	else if (ft_strcmp_dnd(input[1], "sleight_of_hand") == 0)
		ft_skill_throw(info, "sleight_of_hand",
			info->stats.dex, info->skill_mod.sleight_of_hand);
	else if (ft_strcmp_dnd(input[1], "stealth") == 0)
		ft_skill_throw(info, "stealth", info->stats.dex, info->skill_mod.stealth);
	else if (ft_strcmp_dnd(input[1], "arcana") == 0)
		ft_skill_throw(info, "arcana", info->stats.inte, info->skill_mod.arcana);
	else if (ft_strcmp_dnd(input[1], "history") == 0)
		ft_skill_throw(info, "history", info->stats.inte, info->skill_mod.history);
	else if (ft_strcmp_dnd(input[1], "investigation") == 0)
		ft_skill_throw(info, "investigation",
			info->stats.inte, info->skill_mod.investigation);
	else if (ft_strcmp_dnd(input[1], "nature") == 0)
		ft_skill_throw(info, "nature", info->stats.inte, info->skill_mod.nature);
	else if (ft_strcmp_dnd(input[1], "religion") == 0)
		ft_skill_throw(info, "religion", info->stats.inte, info->skill_mod.religion);
	else if (ft_strcmp_dnd(input[1], "animal_handling") == 0)
		ft_skill_throw(info, "animal_handling",
			info->stats.wis, info->skill_mod.animal_handling);
	else if (ft_strcmp_dnd(input[1], "insight") == 0)
		ft_skill_throw(info, "insight", info->stats.wis, info->skill_mod.insight);
	else if (ft_strcmp_dnd(input[1], "medicine") == 0)
		ft_skill_throw(info, "medicine", info->stats.wis, info->skill_mod.medicine);
	else if (ft_strcmp_dnd(input[1], "perception") == 0)
		ft_skill_throw(info, "perception", info->stats.wis, info->skill_mod.perception);
	else if (ft_strcmp_dnd(input[1], "survival") == 0)
		ft_skill_throw(info, "survival", info->stats.wis, info->skill_mod.survival);
	else if (ft_strcmp_dnd(input[1], "deception") == 0)
		ft_skill_throw(info, "deception", info->stats.cha, info->skill_mod.deception);
	else if (ft_strcmp_dnd(input[1], "intimidation") == 0)
		ft_skill_throw(info, "intimidation", info->stats.cha, info->skill_mod.intimidation);
	else if (ft_strcmp_dnd(input[1], "performance") == 0)
		ft_skill_throw(info, "performance", info->stats.cha, info->skill_mod.performance);
	else if (ft_strcmp_dnd(input[1], "persuasion") == 0)
		ft_skill_throw(info, "persuasion", info->stats.cha, info->skill_mod.persuasion);
	else if (ft_strcmp_dnd(input[1], "initiative") == 0)
		ft_check_initiative(info);
	else 
		ft_printf("4-Invalid command given\n");
	return ;
}

int	ft_npc_open_file(t_char *info)
{
	int		error;
	int		fd;
	char	**content;
	
	fd = open(info->save_file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(2, "1-Error opening file %s: %s\n",
			info->save_file, strerror(errno));
		return (1);
	}
	content = ft_read_file_dnd(fd);
	if (!content)
	{
		ft_printf_fd(2, "Malloc in read file failed");
		return (1);
	}
	close(fd);
	error = ft_initialize_info(info, content);
	if (error)
		return (error);
	error = ft_npc_check_info(info);
	ft_print_content(content);
	ft_free_content(content);
	if (error)
		error = 1;
	return (error);
}

void	ft_npc_change_stats(t_char *info, int index, char **input)
{
	int	error;

	if (index == 2)
	{
		if (ft_strcmp_dnd(input[1], "init") == 0)
		{
			ft_npc_write_file(info, &info->dstats);
			ft_printf("Stats for %s written on a file\n", info->name);
			return ;
		}
	}
	error = ft_npc_open_file(info);
	if (error)
		return ;
	error = ft_npc_check_info(info);
	if (error)
		return ;
	if (index == 1)
	{
		if (info->turn)
			info->turn(info);
		else
			ft_printf("No turn set for %s\n", info->name);
	}
	else if (index == 2)
		ft_npc_sstuff(info, input);
	else if (index == 3)
		ft_npc_set_stat(info, input);
	else if (index > 3)
		ft_printf_fd(2, "Error: too manny arguments given\n");
	ft_npc_write_file(info, &info->stats);
	return ;
}
