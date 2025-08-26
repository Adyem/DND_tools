#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/ReadLine/readline.hpp"

inline static bool ft_is_crackback_possible(t_char * info, int number)
{
    return (number < 10 && !info->flags.reaction_used);
}

inline static void ft_notify_no_weapon(t_char * info, const char *weapon_type)
{
    pf_printf_fd(2, "No %s set for %s\n", weapon_type, info->name);
    return ;
}

static bool ft_handle_attack_choice(t_char * info, const char *choice)
{
    if (ft_strcmp_dnd(choice, "melee") == 0)
    {
        if (info->equipment.weapon.attack.function)
        {
            info->equipment.weapon.attack.function(info, &info->equipment.weapon, 0);
            info->flags.reaction_used = 1;
            return (true);
        }
        else
        {   
            ft_notify_no_weapon(info, "mainhand weapon");
            return (false);
        }
    }
    else if (ft_strcmp_dnd(choice, "ranged") == 0)
    {
        if (info->equipment.ranged_weapon.attack.function)
        {
            info->equipment.ranged_weapon.attack.function(info, &info->equipment.ranged_weapon, 0);
            info->flags.reaction_used = 1;
            return (true);
        }
        else
        {
            ft_notify_no_weapon(info, "ranged weapon");
            return (false);
        }
    }
    return (false);
}

static void ft_execute_crackback(t_char * info)
{
    char *line;
    int max_tries = 0;
    bool melee_missing = false;
    bool ranged_missing = false;

    while (true)
    {
        line = rl_readline("CRACKBACK: ranged or melee attack or type exit to do nothing: ");
        if (!line)
        {
            pf_printf_fd(2, "117-Error: failed to allocate memory for readline %s\n", info->name);
            return ;
        }

        if (ft_strcmp_dnd(line, "exit") == 0)
        {
            cma_free(line);
            return ;
        }
        else if (ft_handle_attack_choice(info, line))
        {
            cma_free(line);
            break ;
        }
        else
        {
            if (ft_strcmp_dnd(line, "melee") == 0)
                melee_missing = true;
            else if (ft_strcmp_dnd(line, "ranged") == 0)
                ranged_missing = true;

            pf_printf_fd(2, "118-Error: Invalid input Crackback, valid inputs are melee, " \
                    "ranged or exit\n");
            cma_free(line);
        }

        max_tries++;
        if ((melee_missing && ranged_missing) || info->flags.reaction_used || max_tries >= 10)
            break ;
    }
    return ;
}

void ft_crackback(t_char * info, int number)
{
    if (!ft_is_crackback_possible(info, number))
        return ;
    pf_printf("Because of the low attack roll %s has the opportunity to react with " \
            "an opportunity attack\n", info->name);
    ft_execute_crackback(info);
    return ;
}
