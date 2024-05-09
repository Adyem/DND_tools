#include "dnd_tools.h"

int	ft_free_request_damage(char *line, char **input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
	free(line);
	return (1);
}

int	ft_request_damage(t_char *info)
{
	char	**input;
	char	*line;
	int		fail;
	
	fail = 0;
	while ((line = readline("How much damage was dealt: ")))
	{
		if (!line)
			return (1);
		if (ft_strcmp_dnd(line, "exit") == 0)
		{
			ft_deal_damage(info, NULL, NULL, 0, 2);
			free(line);
			return (0);
		}
		input = ft_split(line, ' ');
		if (!input)
		{
			if (!fail)
			{
				free(line);
				fail = 1;
				continue ;
			}
			else
			{
				free(line);
				return (1);
			}
		}
		if (ft_check_value(input[0]))
		{
			ft_free_request_damage(line, input);
			ft_printf_fd(2, "1-Requesting a number between 1 and 5000\n");
			continue ;
		}
		if (!input[0] || !input[1])
		{
			ft_free_request_damage(line, input);
			continue ;
		}
		if (info->version_number < 2)
			ft_deal_damage(info, input[0], NULL, 0, 0);
		else if (ft_strcmp_dnd(input[1], "acid") == 0)
			ft_deal_damage(info, input[0], "acid", info->c_resistance.acid, 0);
		else if (ft_strcmp_dnd(input[1], "bludgeoning") == 0)
			ft_deal_damage(info, input[0], "bludgeoning", info->c_resistance.bludgeoning, 0);
		else if (ft_strcmp_dnd(input[1], "cold") == 0)
			ft_deal_damage(info, input[0], "cold", info->c_resistance.cold, 0);
		else if (ft_strcmp_dnd(input[1], "fire") == 0)
			ft_deal_damage(info, input[0], "fire", info->c_resistance.fire, 0);
		else if (ft_strcmp_dnd(input[1], "force") == 0)
			ft_deal_damage(info, input[0], "force", info->c_resistance.force, 0);
		else if (ft_strcmp_dnd(input[1], "lightning") == 0)
			ft_deal_damage(info, input[0], "lightning", info->c_resistance.lightning, 0);
		else if (ft_strcmp_dnd(input[1], "necrotic") == 0)
			ft_deal_damage(info, input[0], "necrotic", info->c_resistance.necrotic, 0);
		else if (ft_strcmp_dnd(input[1], "piercing") == 0)
			ft_deal_damage(info, input[0], "piercing", info->c_resistance.piercing, 0);
		else if (ft_strcmp_dnd(input[1], "poison") == 0)
			ft_deal_damage(info, input[0], "poison", info->c_resistance.poison, 0);
		else if (ft_strcmp_dnd(input[1], "psychic") == 0)
			ft_deal_damage(info, input[0], "psychic", info->c_resistance.psychic, 0);
		else if (ft_strcmp_dnd(input[1], "radiant") == 0)
			ft_deal_damage(info, input[0], "radiant", info->c_resistance.radiant, 0);
		else if (ft_strcmp_dnd(input[1], "slashing") == 0)
			ft_deal_damage(info, input[0], "slashing", info->c_resistance.slashing, 0);
		else if (ft_strcmp_dnd(input[1], "thunder") == 0)
			ft_deal_damage(info, input[0], "thunder", info->c_resistance.thunder, 0);
	}
	ft_free_request_damage(line, input);
	return (0);
}
