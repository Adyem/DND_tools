#include "dnd_tools.h"

static int	ft_free_request_damage(char *line, char **input)
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

int ft_get_resistance(t_char *info, const char *type)
{
	if (strcmp(type, "acid") == 0)
		return info->c_resistance.acid;
	else if (strcmp(type, "bludgeoning") == 0)
		return info->c_resistance.bludgeoning;
	else if (strcmp(type, "cold") == 0)
		return info->c_resistance.cold;
	else if (strcmp(type, "fire") == 0)
		return info->c_resistance.fire;
	else if (strcmp(type, "force") == 0)
		return info->c_resistance.force;
	else if (strcmp(type, "lightning") == 0)
		return info->c_resistance.lightning;
	else if (strcmp(type, "necrotic") == 0)
		return info->c_resistance.necrotic;
	else if (strcmp(type, "piercing") == 0)
		return info->c_resistance.piercing;
	else if (strcmp(type, "poison") == 0)
		return info->c_resistance.poison;
	else if (strcmp(type, "psychic") == 0)
		return info->c_resistance.psychic;
	else if (strcmp(type, "radiant") == 0)
		return info->c_resistance.radiant;
	else if (strcmp(type, "slashing") == 0)
		return info->c_resistance.slashing;
	else if (strcmp(type, "thunder") == 0)
		return info->c_resistance.thunder;
	return (-9999);
}

int	ft_request_damage(t_char *info)
{
	char	**input;
	char	*line;
	int		fail;
	int		resistance;
	
	fail = 0;
	input = NULL;
	while ((line = readline("How much damage was dealt: ")))
	{
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
			ft_printf_fd(2, "159-Requesting a number between 1 and 5000\n");
			continue ;
		}
		if (!input[0] || !input[1])
		{
			ft_free_request_damage(line, input);
			continue ;
		}
		if (info->version_number < 2)
			ft_deal_damage(info, input[0], NULL, 0, 0);
		else
		{
			resistance = ft_get_resistance(info, input[1]);
			if (resistance == -9999)
				return (ft_printf_fd(2, "158-Error getting Resistance %s\n",
					info->name), 1);
			ft_deal_damage(info, input[0], input[1], resistance, 0);
		}
		ft_free_request_damage(line, input);
		line = NULL;
		input = NULL;
	}
	ft_free_request_damage(line, input);
	return (0);
}
