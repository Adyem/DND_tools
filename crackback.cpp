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

	ranged = 0;
	melee = 0;
	if (number < 10 && !info->flags.reaction_used)
	{
		ft_printf("because of the low attack roll %s has the oppertunity to react with an " \
				"oppertunity attack\n", info->name);
		while (1)
		{
			line = rl_readline("CRACKBACK: ranged or melee attack or type exit to do nothing: ");
			if (!line)
				return (ft_printf_fd(2, "117-Error: failed to allocate memory for readline %s\n",
							info->name), (void)0);
			if (ft_strcmp_dnd(line, "melee"))
			{
				if (info->equipment.weapon.attack.function)
				{
					info->equipment.weapon.attack.function(info, &info->equipment.weapon, 0);
					info->flags.reaction_used = 1;
				}
				else
				{	
					ft_printf_fd(2, "No MH weapon set for %s\n", info->name);
					melee = 1;
				}
			}
			else if (ft_strcmp_dnd(line, "ragned"))
			{
				if (info->equipment.ranged_weapon.attack.function)
				{
					info->equipment.ranged_weapon.attack.function(info,
							&info->equipment.weapon, 0);
					info->flags.reaction_used = 1;
				}
				else
				{
					ft_printf_fd(2, "No ranged weapon set for %s\n", info->name);
					ranged = 1;
				}
			}
			else if (ft_strcmp_dnd(line, "exit"))
			{
				cma_free(line);
				return ;
			}
			else 
			{
				ft_printf_fd(2, "118-Error: Invalid input Crackback\n");
				cma_free(line);
				continue ;
			}
			cma_free(line);
			if ((melee && ranged) || info->flags.reaction_used)
				return ;
		}
	}
	return ;
}
