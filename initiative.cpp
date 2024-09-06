#include "dnd_tools.hpp"
#include "libft/printf/ft_printf.hpp"

void	ft_check_initiative(t_char *info)
{
	if (info->initiative == -1)
		ft_printf("No initative set for %s\n", info->name);
	else
		ft_printf("%s has an initiative roll of %i\n", info->name, info->initiative);
	return ;
}

void	ft_roll_initiative(t_char *info)
{
	int dex_mod;
	int	result;

	dex_mod = (info->stats.dex - 10) / 2;
	result = ft_dice_roll(1, 20);
	info->initiative = result + dex_mod;
	ft_printf("%s rolled %i+%i=%i on his/her initiative\n",
			info->name, result, dex_mod, info->initiative);
	return ;
}
