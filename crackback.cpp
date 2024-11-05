#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/ReadLine/readline.hpp"

void ft_crackback(t_char *info, int number)
{
	char	*line;
	int		ranged;
	int		melee;
	int		max_tries;

	max_tries = 0;
	ranged = 0;
	melee = 0;
	if (number < 10 && !info->flags.reaction_used)
	{
		pf_printf("Because of the low attack roll %s has the opportunity to react with an " \
				"opportunity attack\n", info->name);
		while (1)
		{
			line = rl_readline("CRACKBACK: ranged or melee attack or type exit to do nothing: ");
			if (!line)
			{
				pf_printf_fd(2, "117-Error: failed to allocate memory for readline %s\n",
						info->name);
				return ;
			}
			if (ft_strcmp_dnd(line, "melee") == 0)
			{
				if (info->equipment.weapon.attack.function)
				{
					info->equipment.weapon.attack.function(info, &info->equipment.weapon, 0);
					info->flags.reaction_used = 1;
				}
				else
				{	
					pf_printf_fd(2, "No mainhand weapon set for %s\n", info->name);
					melee = 1;
				}
			}
			else if (ft_strcmp_dnd(line, "ranged") == 0)
			{
				if (info->equipment.ranged_weapon.attack.function)
				{
					info->equipment.ranged_weapon.attack.function(info,
							&info->equipment.ranged_weapon, 0);
					info->flags.reaction_used = 1;
				}
				else
				{
					pf_printf_fd(2, "No ranged weapon set for %s\n", info->name);
					ranged = 1;
				}
			}
			else if (ft_strcmp_dnd(line, "exit") == 0)
			{
				cma_free(line);
				return ;
			}
			else 
			{
				pf_printf_fd(2, "118-Error: Invalid input Crackback, valid inputs are " \
						"melee, ranged or exit\n");
				cma_free(line);
				continue ;
			}
			cma_free(line);
			max_tries++;
			if ((melee && ranged) || info->flags.reaction_used || max_tries >= 10)
				return ;
		}
	}
	return ;
}
