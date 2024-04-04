#include "dnd_tools.h"

void	ft_update_lightning_strike(t_char *info)
{
	int	result;

	if (!info->bufs.lightning_strike.dice_amount ||
		!info->bufs.lightning_strike.dice_faces ||
		!info->bufs.lightning_strike.distance)
		return ;
	info->bufs.lightning_strike.duration--;
	if (info->bufs.lightning_strike.duration == 0)
	{
		result = ft_dice_roll(1, 8) + info->bufs.lightning_strike.extra_damage;
		ft_printf("%s his lightning strike markers explode dealing %i lightning damage to" \
				" annyone standing within %i ft.\n",
				info->name, result, info->bufs.lightning_strike.distance);
	}
	else if (info->bufs.lightning_strike.duration == 1)
		ft_printf("%s his lightning strike markers will explode on his next turn\n",
				info->name);
	else
		ft_printf("%s his lightning strike  markers will explode in %i turns\n",
				info->name, info->bufs.lightning_strike.duration);
	return ;
}
