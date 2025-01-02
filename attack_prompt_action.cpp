#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/shared_ptr.hpp"
#include "libft/ReadLine/readline.hpp"

typedef void (*t_spellcast_func)(ft_sharedptr<t_char> &character, bool critical_strike);

typedef struct s_known_spell
{
    const char      *cmd;
    int             *learned;
    t_spellcast_func cast_func;
}   t_known_spell;

void ft_prompt_smite_on_attack_success(ft_sharedptr<t_char> &character, bool critical_strike)
{
    t_known_spell known_spells[] = {
        {
            "divine_smite",
            &character->spells.divine_smite.learned,
            ft_cast_divine_smite
        },
        { nullptr, nullptr, nullptr }
    };
    pf_printf("You have the following learned spells available:\n");
	int index = 0;
	int not_learned = 0;
    while (known_spells[index].cmd != nullptr)
    {
		if (*(known_spells[index].learned) != 0)
            pf_printf(" - %s\n", known_spells[index].cmd);
		else
			not_learned++;
		index++;
    }
	if (not_learned == index)
		return ;
    pf_printf("Type the spell name to cast it, or type 'exit' to skip.\n");
    int invalid_attempts = 0;
    char *input = ft_nullptr;
    while ((input = rl_readline("Cast a learned spell or type 'exit': ")) != ft_nullptr)
    {
        if (ft_strcmp_dnd(input, "exit") == 0)
        {
            pf_printf("Exiting spell prompt.\n");
            cma_free(input);
            break;
        }
        bool found_spell = false;
		int index = 0;
        while (known_spells[index].cmd != nullptr)
        {
            if (ft_strcmp_dnd(input, known_spells[index].cmd) == 0)
            {
                if (*(known_spells[index].learned) == 0)
                {
                    pf_printf("You have not learned %s.\n", known_spells[index].cmd);
                    found_spell = true;
                    break;
                }
                known_spells[index].cast_func(character, critical_strike);
                found_spell = true;
                break;
            }
			index++;
        }
        if (!found_spell)
        {
            invalid_attempts++;
            if (invalid_attempts >= 5)
            {
                pf_printf("Too many invalid attempts. Exiting spell prompt.\n");
                cma_free(input);
                break;
            }
            pf_printf("Invalid input. Type a learned spell name or 'exit' (Attempt %d/5).\n",
                      invalid_attempts);
        }
        cma_free(input);
    }
	if (input == ft_nullptr)
        pf_printf_fd(2, "Error: read line memory allocation failed\n");
	return ;
}
