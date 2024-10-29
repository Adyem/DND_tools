#include "character.hpp"
#include "libft/Printf/ft_printf.hpp"

void ft_crackback(t_char *info, int number)
{
	if (info->feats.crackback.active == 0 && number < 10 && !info->flags.reaction_used)
	{
		ft_printf("because of the low attack roll %s has the oppertunity to react with an " \
				"oppertunity attack", info->name);
		if (info->equipment.weapon.attack.function)
			info->equipment.weapon.attack.function(info, &info->equipment.weapon, 0);
		else
			ft_printf_fd(2, "No MH weapon set for %s", info->name);
		info->flags.reaction_used = 1;
	}
	return ;
}
