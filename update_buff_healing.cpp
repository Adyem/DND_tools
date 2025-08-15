#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/RNG/RNG.hpp"

void	ft_update_buff_rejuvenation(t_char *info)
{
	t_buff_rejuvenation *rejuvenation = &info->bufs.rejuvenation;
	int result = ft_dice_roll(rejuvenation->healing_dice_amount,
			rejuvenation->healing_dice_faces) + rejuvenation->healing_extra;
	pf_printf("rejuvenation heals %s for %i at the start of his/her turn", info->name, result);
	info->bufs.rejuvenation.duration--;
	if (rejuvenation->duration == 0)
	{
		rejuvenation->healing_extra = 0;
		rejuvenation->healing_dice_faces = 0;
		rejuvenation->healing_dice_amount = 0;
	}
	return ;
}
