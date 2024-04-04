#include "dnd_tools.h"

int	ft_check_bless(t_char *info)
{
	int	result;

	result = 0;
	if (info->bufs.bless.duration > 0)
		result += ft_dice_roll(1, 4);
	else
		return (0);
	ft_printf("%s rolled a %i as an additional modifier for his/her bless buff\n",
			info->name, result);
	return (result);
}
