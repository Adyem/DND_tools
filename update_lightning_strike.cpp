#include "dnd_tools.hpp"
#include "libft/printf/ft_printf.hpp"
#include "libft/printf_fd/ft_printf_fd.hpp"

void	ft_npc_update_lightning_strike(t_char *info, const char **input)
{
	int	number;

	if (ft_check_value(input[2]))
	{
		ft_printf_fd(2, "1-Lightning strike expecting a number between 0 and 1\n");
		return ;
	}
	number = ft_atoi(input[2]);
	if (number >= 0 && number <= 1)
	{
		if (info->bufs.lightning_strike.duration == 0 && number == 0)
			ft_printf("%s  has lightning markers up at the moment\n", info->name);
		else if (info->bufs.lightning_strike.duration == 0 && number > 0)
		{
			if (info->bufs.lightning_strike.amount == 1)
				ft_printf("%s made a lightning strike marker appear\n", info->name);
			else
				ft_printf("%s made %i lightning strike markers appear\n",
					info->name, info->bufs.lightning_strike.amount);
		}
		else if (info->bufs.lightning_strike.duration > 0 && number == 0)
			ft_printf("%s all lightning strike markers are gone\n", info->name);
		else if (info->bufs.lightning_strike.duration > 0 && number > 0)
		{
			ft_printf("old lightning strike markers have disappeared\n");
			if (info->bufs.lightning_strike.amount == 1)
				ft_printf("%s has made a lightning strike marker appear", info->name);
			else
				ft_printf("%s has made %i lightning strike markers appear",
						info->name, info->bufs.lightning_strike.amount);
		}
		info->bufs.lightning_strike.duration = number;
	}
	else
		ft_printf_fd(2, "2-Lightning strike expecting a number between 0 and 1");
}
