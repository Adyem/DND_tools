#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <readline/readline.h>

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
	if (ft_strcmp_dnd(type, "acid") == 0)
		return (ft_calculate_acid_resistance(info));
	else if (ft_strcmp_dnd(type, "bludgeoning") == 0)
		return (ft_calculate_bludgeoning_resistance(info));
	else if (ft_strcmp_dnd(type, "cold") == 0)
		return (ft_calculate_cold_resistance(info));
	else if (ft_strcmp_dnd(type, "fire") == 0)
		return (ft_calculate_fire_resistance(info));
	else if (ft_strcmp_dnd(type, "force") == 0)
		return (ft_calculate_force_resistance(info));
	else if (ft_strcmp_dnd(type, "lightning") == 0)
		return (ft_calculate_lightning_resistance(info));
	else if (ft_strcmp_dnd(type, "necrotic") == 0)
		return (ft_calculate_necrotic_resistance(info));
	else if (ft_strcmp_dnd(type, "piercing") == 0)
		return (ft_calculate_piercing_resistance(info));
	else if (ft_strcmp_dnd(type, "poison") == 0)
		return (ft_calculate_poison_resistance(info));
	else if (ft_strcmp_dnd(type, "psychic") == 0)
		return (ft_calculate_psychic_resistance(info));
	else if (ft_strcmp_dnd(type, "radiant") == 0)
		return (ft_calculate_radiant_resistance(info));
	else if (ft_strcmp_dnd(type, "slashing") == 0)
		return (ft_calculate_slashing_resistance(info));
	else if (ft_strcmp_dnd(type, "thunder") == 0)
		return (ft_calculate_thunder_resistance(info));
	return (-9999);
}

int ft_request_damage(t_char *info)
{
    char	**input = nullptr;
    char	*line = nullptr;
    int		fail = 0;
    int		resistance;

    while ((line = readline("How much damage was dealt: ")))
    {
        if (ft_strcmp_dnd(line, "exit") == 0)
        {
            ft_deal_damage(info, nullptr, nullptr, 0, 2);
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
            std::cerr << "159-Requesting a number between 1 and 5000" << std::endl;
            continue ;
        }
        if (!input[0] || !input[1])
        {
            ft_free_request_damage(line, input);
            continue ;
        }
        resistance = ft_get_resistance(info, input[1]);
        if (resistance == -9999)
        {
            std::cerr << "158-Error getting Resistance for " << info->name << std::endl;
            ft_free_request_damage(line, input);
            return (1);
        }
        ft_deal_damage(info, input[0], input[1], resistance, 0);
        ft_free_request_damage(line, input);
        line = nullptr;
        input = nullptr;
    }
    ft_free_request_damage(line, input);
    return (0);
}
