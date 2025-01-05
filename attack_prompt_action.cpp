#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/shared_ptr.hpp"
#include "libft/ReadLine/readline.hpp"
#include "character.hpp"

static void list_learned_spells(t_known_spell known_spells[])
{
    pf_printf("You have the following learned spells available:\n");
    int index = 0;
    while (known_spells[index].cmd != nullptr)
    {
        if (*(known_spells[index].learned) != 0)
            pf_printf(" - %s\n", known_spells[index].cmd);
        index++;
    }
	return ;
}

static bool all_spells_not_learned(t_known_spell known_spells[])
{
    int index = 0;
    int not_learned = 0;
    while (known_spells[index].cmd != nullptr)
    {
        if (*(known_spells[index].learned) == 0)
            not_learned++;
        index++;
    }
    return (not_learned == index);
}

static bool handle_spell_cast(ft_sharedptr<t_char> &character, t_known_spell known_spells[],
								char *input, bool critical_strike)
{
    int index = 0;
    while (known_spells[index].cmd != nullptr)
    {
        if (ft_strcmp_dnd(input, known_spells[index].cmd) == 0)
        {
            if (*(known_spells[index].learned) == 0)
            {
                pf_printf("You have not learned %s.\n", known_spells[index].cmd);
                return (true);
            }
            known_spells[index].cast_func(character, critical_strike);
            cma_free(input);
            return (true);
        }
        index++;
    }
    return (false);
}

static void prompt_user_for_spell(t_known_spell known_spells[], ft_sharedptr<t_char> &character,
							bool critical_strike)
{
    pf_printf("Type the spell name to cast it, or type 'exit' to skip.\n");
    int invalid_attempts = 0;
    char *input = ft_nullptr;
	while ((input = rl_readline("Cast a learned spell or type 'exit': ")) != ft_nullptr)
	{
        if (ft_strcmp_dnd(input, "exit") == 0)
        {
            pf_printf("Exiting spell prompt.\n");
            cma_free(input);
            break ;
        }
        bool found_spell = handle_spell_cast(character, known_spells, input, critical_strike);
        if (found_spell)
            return ;
        invalid_attempts++;
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

void ft_prompt_on_attack_success(ft_sharedptr<t_char> &character, bool critical_strike)
{
    t_known_spell known_spells[] = {
        {
            "divine_smite",
            &character->spells.divine_smite.learned,
            ft_cast_divine_smite
        },
        { nullptr, nullptr, nullptr }
    };
    list_learned_spells(known_spells);
    if (all_spells_not_learned(known_spells))
        return ;
    prompt_user_for_spell(known_spells, character, critical_strike);
	return ;
}
