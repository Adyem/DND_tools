#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/Template/vector.hpp"
#include "character.hpp"

static int ft_append_spell(ft_vector<t_known_spell> &known_spells,
            const char *command,
            int *learned,
            t_spellcast_func cast_func)
{
    t_known_spell   entry;

    entry.cmd = command;
    entry.learned = learned;
    entry.cast_func = cast_func;
    known_spells.push_back(entry);
    if (known_spells.get_error() != ER_SUCCESS)
    {
        ft_errno = known_spells.get_error();
        return (-1);
    }
    return (0);
}

int ft_collect_known_spells(t_char * character, ft_vector<t_known_spell> &known_spells)
{
    if (!character)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (-1);
    }
    known_spells.clear();
    if (known_spells.get_error() != ER_SUCCESS)
    {
        ft_errno = known_spells.get_error();
        return (-1);
    }
    if (ft_append_spell(known_spells,
            "divine_smite",
            &character->spells.divine_smite.learned,
            ft_cast_divine_smite) != 0)
        return (-1);
    ft_errno = ER_SUCCESS;
    return (0);
}

static int ft_list_learned_spells(ft_vector<t_known_spell> &known_spells)
{
    size_t  count;
    size_t  index;
    int     first_spell;

    count = known_spells.size();
    if (known_spells.get_error() != ER_SUCCESS)
    {
        ft_errno = known_spells.get_error();
        return (-1);
    }
    index = 0;
    first_spell = 0;
    while (index < count)
    {
        t_known_spell   &spell = known_spells[index];

        if (known_spells.get_error() != ER_SUCCESS)
        {
            ft_errno = known_spells.get_error();
            return (-1);
        }
        if (*(spell.learned) != 0)
        {
            if (first_spell == 0)
            {
                pf_printf("You have the following learned spells available:\n");
                first_spell = 1;
            }
            pf_printf(" - %s\n", spell.cmd);
        }
        index = index + 1;
    }
    return (0);
}

static int ft_all_spells_not_learned(ft_vector<t_known_spell> &known_spells, int *result)
{
    size_t  count;
    size_t  index;
    size_t  not_learned;

    count = known_spells.size();
    if (known_spells.get_error() != ER_SUCCESS)
    {
        ft_errno = known_spells.get_error();
        return (-1);
    }
    index = 0;
    not_learned = 0;
    while (index < count)
    {
        t_known_spell   &spell = known_spells[index];

        if (known_spells.get_error() != ER_SUCCESS)
        {
            ft_errno = known_spells.get_error();
            return (-1);
        }
        if (*(spell.learned) == 0)
            not_learned = not_learned + 1;
        index = index + 1;
    }
    *result = (not_learned == count);
    return (0);
}

static int ft_handle_spell_cast(t_char * character,
            ft_vector<t_known_spell> &known_spells,
            const char *input,
            bool critical_strike)
{
    size_t  count;
    size_t  index;

    count = known_spells.size();
    if (known_spells.get_error() != ER_SUCCESS)
    {
        ft_errno = known_spells.get_error();
        return (-1);
    }
    index = 0;
    while (index < count)
    {
        t_known_spell   &spell = known_spells[index];

        if (known_spells.get_error() != ER_SUCCESS)
        {
            ft_errno = known_spells.get_error();
            return (-1);
        }
        if (ft_strcmp(input, spell.cmd) == 0)
        {
            if (*(spell.learned) == 0)
            {
                pf_printf("You have not learned %s.\n", spell.cmd);
                return (1);
            }
            spell.cast_func(character, critical_strike);
            return (2);
        }
        index = index + 1;
    }
    return (0);
}

static void ft_prompt_user_for_spell(ft_vector<t_known_spell> &known_spells,
            t_char * character,
            bool critical_strike)
{
    int     invalid_attempts;
    char    *input;

    pf_printf("Type the spell name to cast it, or type 'exit' to skip.\n");
    invalid_attempts = 0;
    input = ft_nullptr;
    while ((input = rl_readline("Cast a learned spell or type 'exit': ")) != ft_nullptr)
    {
        if (ft_strcmp(input, "exit") == 0)
        {
            pf_printf("Exiting spell prompt.\n");
            cma_free(input);
            break ;
        }
        int status = ft_handle_spell_cast(character, known_spells, input, critical_strike);

        if (status == -1)
        {
            pf_printf_fd(2, "Error resolving spell command: %s\n", ft_strerror(ft_errno));
            cma_free(input);
            return ;
        }
        if (status == 1 || status == 2)
        {
            cma_free(input);
            return ;
        }
        invalid_attempts = invalid_attempts + 1;
        if (invalid_attempts >= 5)
        {
            pf_printf("Too many invalid attempts. Exiting spell prompt.\n");
            cma_free(input);
            break ;
        }
        pf_printf("Invalid input. Type a learned spell name or 'exit' (Attempt %d/5).\n",
            invalid_attempts);
        cma_free(input);
    }
    if (input == ft_nullptr)
        pf_printf_fd(2, "Error: read line memory allocation failed\n");
    return ;
}

void ft_prompt_on_attack_success(t_char * character, bool critical_strike)
{
    ft_vector<t_known_spell>    known_spells(4);
    int                         all_not_learned;

    if (known_spells.get_error() != ER_SUCCESS)
    {
        ft_errno = known_spells.get_error();
        pf_printf_fd(2, "Error initializing known spell storage: %s\n",
            ft_strerror(ft_errno));
        return ;
    }
    if (ft_collect_known_spells(character, known_spells) != 0)
    {
        pf_printf_fd(2, "Error collecting known spells: %s\n", ft_strerror(ft_errno));
        return ;
    }
    if (ft_list_learned_spells(known_spells) != 0)
    {
        pf_printf_fd(2, "Error listing known spells: %s\n", ft_strerror(ft_errno));
        return ;
    }
    if (ft_all_spells_not_learned(known_spells, &all_not_learned) != 0)
    {
        pf_printf_fd(2, "Error calculating spell availability: %s\n",
            ft_strerror(ft_errno));
        return ;
    }
    if (all_not_learned)
        return ;
    ft_prompt_user_for_spell(known_spells, character, critical_strike);
    return ;
}
