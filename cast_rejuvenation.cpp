#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"

void	ft_cast_rejuvenation(const char **input, t_char *info)
{
	t_char *target = ft_nullptr;
    if (ft_set_stats_check_name(input[3]))
    {
        if (ft_check_player_character(input[3]))
            return ;
    }
    else
    {
        target = ft_get_info(input[3], info->struct_name);
        if (!target)
			pf_printf_fd(2, "155-Error getting info %s\n", input[2]);
    }
	if (target)
	{
		target->bufs.rejuvenation.duration = info->spells.rejuvenation.duration;
		target->bufs.rejuvenation.healing_extra = info->spells.rejuvenation.healing_extra;
		target->bufs.rejuvenation.healing_dice_faces = info->spells.rejuvenation.healing_dice_faces;
		target->bufs.rejuvenation.healing_dice_amount =
			info->spells.rejuvenation.healing_dice_amount;
	}
	const char *target_name = ft_nullptr;
	if (target)
		target_name = target->name;
	else
		target_name = "target";
	pf_printf("%s just cast rejuvenation on %s, for the next %i turns at the start of his/her" \
			"turn will heal for %id%i + %i\n", info->name, target_name,
			info->spells.rejuvenation.duration, info->spells.rejuvenation.healing_dice_amount,
			info->spells.rejuvenation.healing_dice_faces, info->spells.rejuvenation.healing_extra);
	return ;
}
