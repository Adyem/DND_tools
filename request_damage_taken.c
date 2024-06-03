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

int ft_get_resistance(t_char *info, char *type)
{
	if (strcmp(type, "acid") == 0)
		return info->c_resistance.acid;
	if (strcmp(type, "bludgeoning") == 0)
		return info->c_resistance.bludgeoning;
	if (strcmp(type, "cold") == 0)
		return info->c_resistance.cold;
	if (strcmp(type, "fire") == 0)
		return info->c_resistance.fire;
	if (strcmp(type, "force") == 0)
		return info->c_resistance.force;
	if (strcmp(type, "lightning") == 0)
		return info->c_resistance.lightning;
	if (strcmp(type, "necrotic") == 0)
		return info->c_resistance.necrotic;
	if (strcmp(type, "piercing") == 0)
		return info->c_resistance.piercing;
	if (strcmp(type, "poison") == 0)
		return info->c_resistance.poison;
	if (strcmp(type, "psychic") == 0)
		return info->c_resistance.psychic;
	if (strcmp(type, "radiant") == 0)
		return info->c_resistance.radiant;
	if (strcmp(type, "slashing") == 0)
		return info->c_resistance.slashing;
	if (strcmp(type, "thunder") == 0)
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
		else
		{
			resistance = ft_get_resistance(info, input[1]);
			ft_deal_damage(info, input[0], input[1], resistance, 0);
		}
	}
	ft_free_request_damage(line, input);
	return (0);
}
