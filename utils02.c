#include "dnd_tools.h"

void ft_print_character_status(t_char *info, int number, int temp)
{
	if (number == 0 && temp == 0)
		ft_printf("%s remains unchanged and is dead\n", info->name);
	else if (temp == info->dstats.health && info->stats.health == info->dstats.health)
		ft_printf("%s remains at their current state and is at maximum hp (%i)\n",
			info->name, info->dstats.health);
	else if (number == 0)
		ft_printf("%s remains at their current state, with health at %i\n",
			info->name, info->stats.health);
	else if (temp == 0)
	{
		if (number == info->dstats.health)
			ft_printf("%s has been restored to their full health (%i)\n",
				info->name, info->stats.health);
		else if (info->stats.health == info->dstats.health)
			ft_printf("%s has been fully revived from 0 to full %i health with %i surplus"\
					"recovery\n", info->name, info->stats.health,
					number - info->dstats.health);
		else if (info->stats.health > 0)
			ft_printf("%s has been revived with %i health\n", info->name, info->stats.health);
		else
			ft_printf("Efforts on %s were redundant, %i damage was unnecessary\n",
					info->name, number * -1);
	}
	else if (temp == info->dstats.health && info->stats.health == info->dstats.health)
		ft_printf("%s is already at peak condition %i, with %i surplus recovery\n",
			info->name, info->stats.health, number);
	else if (info->stats.health + number > info->dstats.health)
		ft_printf("%s has been fully healed to peak condition %i with %i surplus recovery"\
			"\n", info->name, info->stats.health, temp + number - info->dstats.health);
	else
	{
		if (info->stats.health == 0)
		{
			if ((number * -1) == temp)
				ft_printf("%s encountered a precise setback\n", info->name);
			else
				ft_printf("%s encountered a setback with %i excess damage\n",
					info->name, (number * -1) - temp);
        }
		else if (number < 0)
			ft_printf("%s has recieved %i damage and now has %i health remaining\n",
				info->name, number * -1, info->stats.health);
		else if (number > 0)
			ft_printf("%s's health was enhanced by %i, reaching %i\n",
				info->name, number, info->stats.health);
	}
	return;
}


int	ft_saving_throw(t_char *info, char *ability_score, int ability_mod, int save_mod)
{
	int mod;
	int	result;
	int	roll;

	roll = ft_dice_roll(1, 20);
	mod = ft_save_check_buff(info, &roll, ability_score);
	if (roll <= 1 + info->crit.save_fail)
		ft_printf("%s rolled a critical fail (%i) on his/her %s saving throw\n",
			info->name, roll, ability_score);
	else if (roll >= 20 - info->crit.save)
		ft_printf("%s rolled a crit (%i) on his/her %s saving throw\n",
			info->name, roll, ability_score);
	else
	{
		result = roll + (((ability_mod - 10) / 2) + save_mod + mod);
		ft_printf("%s rolled %i+%i+%i+%i on his/her %s saving throw for a total of %i\n",
			info->name, roll, (ability_mod - 10) / 2, save_mod, mod, ability_score, result);
	}
	return (result);
}

void	ft_skill_throw(t_char *info, char *skill, int ability_mod, int skill_mod)
{
	int mod;
	int	result;
	int	roll;

	roll = ft_dice_roll(1, 20);
	mod = ft_skill_check_buff(info, &result, skill);
	if (roll <= 1 + info->crit.skill_fail)
		ft_printf("%s rolled a critical fail (%i) on his/her %s\n",
			info->name, roll, skill);
	else if (roll >= 20 - info->crit.skill)
		ft_printf("%s rolled a crit (%i) on his/her %s\n",
			info->name, roll, skill);
	else
	{
		result = roll + (((ability_mod - 10) / 2) + skill_mod + mod);
		ft_printf("%s rolled %i+%i+%i+%i on his/her %s for a total of %i\n",
			info->name, roll, (ability_mod - 10) / 2, skill_mod, mod, skill, result);
	}
	return ;
}

void	ft_reroll(t_char *info, int *result)
{
	int second_roll;
	if (info->advantage > 0)
	{
		second_roll = ft_dice_roll(1, 20);
		if (second_roll > *result)
			*result = second_roll;
	}
	else if (info->advantage < 0)
	{
		second_roll = ft_dice_roll(1, 20);
		if (second_roll < *result)
			*result = second_roll;
	}
	return ;
}
