#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/Template/map.hpp"

typedef int (*t_resistance_calculator)(t_char *);

typedef struct s_resistance_entry
{
    const char              *type;
    t_resistance_calculator  calculator;
}   t_resistance_entry;

static int    ft_free_request_damage(char *line, char **input)
{
    cma_free_double(input);
    cma_free(line);
    return (1);
}

static int    ft_initialize_resistance_map(
                ft_map<ft_string, t_resistance_calculator> &map)
{
    t_resistance_entry  entries[] = {
        {DAMAGE_TYPE_ACID, &ft_calculate_acid_resistance},
        {DAMAGE_TYPE_BLUDGEONING, &ft_calculate_bludgeoning_resistance},
        {DAMAGE_TYPE_COLD, &ft_calculate_cold_resistance},
        {DAMAGE_TYPE_FIRE, &ft_calculate_fire_resistance},
        {DAMAGE_TYPE_FORCE, &ft_calculate_force_resistance},
        {DAMAGE_TYPE_LIGHTNING, &ft_calculate_lightning_resistance},
        {DAMAGE_TYPE_NECROTIC, &ft_calculate_necrotic_resistance},
        {DAMAGE_TYPE_PIERCING, &ft_calculate_piercing_resistance},
        {DAMAGE_TYPE_POISON, &ft_calculate_poison_resistance},
        {DAMAGE_TYPE_PSYCHIC, &ft_calculate_psychic_resistance},
        {DAMAGE_TYPE_RADIANT, &ft_calculate_radiant_resistance},
        {DAMAGE_TYPE_SLASHING, &ft_calculate_slashing_resistance},
        {DAMAGE_TYPE_THUNDER, &ft_calculate_thunder_resistance}
    };
    size_t              index;

    index = 0;
    while (index < sizeof(entries) / sizeof(entries[0]))
    {
        ft_string key(entries[index].type);
        if (key.get_error() != ER_SUCCESS)
            return (-1);
        map.insert(key, entries[index].calculator);
        if (map.get_error() != ER_SUCCESS)
            return (-1);
        index++;
    }
    return (0);
}

static ft_map<ft_string, t_resistance_calculator>    &ft_damage_resistance_map(void)
{
    static ft_map<ft_string, t_resistance_calculator> map(16);
    static bool                                        initialized = false;

    if (initialized == false)
    {
        if (ft_initialize_resistance_map(map) != 0)
        {
            map.clear();
            ft_errno = FT_ERR_INVALID_ARGUMENT;
            return (map);
        }
        initialized = true;
    }
    return (map);
}

int ft_get_resistance(t_char * info, const char *type)
{
    ft_map<ft_string, t_resistance_calculator>   &map = ft_damage_resistance_map();
    Pair<ft_string, t_resistance_calculator>     *entry;
    t_resistance_calculator                       calculator;
    ft_string                                     key(type);

    if (!type)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (-9999);
    }
    if (key.get_error() != ER_SUCCESS)
        return (-9999);
    entry = map.find(key);
    if (!entry)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (-9999);
    }
    calculator = entry->value;
    if (!calculator)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (-9999);
    }
    ft_errno = ER_SUCCESS;
    return (calculator(info));
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
        if (ft_validate_int(input[0]))
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
