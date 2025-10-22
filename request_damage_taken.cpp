#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/ReadLine/readline.hpp"

static int    ft_free_request_damage(char *line, char **input)
{
    int    i;

    i = 0;
    while (input && input[i])
    {
        cma_free(input[i]);
        i++;
    }
    cma_free(input);
    cma_free(line);
    return (1);
}

int ft_get_resistance(t_char * info, const char *type)
{
    if (ft_strcmp(type, "acid") == 0)
        return (ft_calculate_acid_resistance(info));
    else if (ft_strcmp(type, "bludgeoning") == 0)
        return (ft_calculate_bludgeoning_resistance(info));
    else if (ft_strcmp(type, "cold") == 0)
        return (ft_calculate_cold_resistance(info));
    else if (ft_strcmp(type, "fire") == 0)
        return (ft_calculate_fire_resistance(info));
    else if (ft_strcmp(type, "force") == 0)
        return (ft_calculate_force_resistance(info));
    else if (ft_strcmp(type, "lightning") == 0)
        return (ft_calculate_lightning_resistance(info));
    else if (ft_strcmp(type, "necrotic") == 0)
        return (ft_calculate_necrotic_resistance(info));
    else if (ft_strcmp(type, "piercing") == 0)
        return (ft_calculate_piercing_resistance(info));
    else if (ft_strcmp(type, "poison") == 0)
        return (ft_calculate_poison_resistance(info));
    else if (ft_strcmp(type, "psychic") == 0)
        return (ft_calculate_psychic_resistance(info));
    else if (ft_strcmp(type, "radiant") == 0)
        return (ft_calculate_radiant_resistance(info));
    else if (ft_strcmp(type, "slashing") == 0)
        return (ft_calculate_slashing_resistance(info));
    else if (ft_strcmp(type, "thunder") == 0)
        return (ft_calculate_thunder_resistance(info));
    return (-9999);
}

int ft_request_damage(t_char * info)
{
    char    **input = ft_nullptr;
    char    *line = ft_nullptr;
    int        fail = 0;
    int        resistance;

    while ((line = rl_readline("How much damage was dealt: ")))
    {
        if (ft_strcmp(line, "exit") == 0)
        {
            ft_deal_damage(info, ft_nullptr, ft_nullptr, 0, 2);
            cma_free(line);
            return (0);
        }
        input = cma_split(line, ' ');
        if (!input)
        {
            if (!fail)
            {
                cma_free(line);
                fail = 1;
                continue ;
            }
            else
            {
                cma_free(line);
                return (1);
            }
        }
        if (ft_check_value(input[0]))
        {
            ft_free_request_damage(line, input);
            pf_printf_fd(2, "159-Requesting a number between 1 and 5000\n");
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
            pf_printf_fd(2, "158-Error getting Resistance for %s\n", info->name);
            ft_free_request_damage(line, input);
            return (1);
        }
        ft_deal_damage(info, input[0], input[1], resistance, 0);
        ft_free_request_damage(line, input);
        line = ft_nullptr;
        input = ft_nullptr;
    }
    ft_free_request_damage(line, input);
    return (0);
}
