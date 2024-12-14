#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"

static void ft_check_buff_damage_hunters_mark(SharedPtr<t_char> info)
{
    int result;

    result = ft_dice_roll(info->concentration.dice_amount_mod, info->concentration.dice_faces_mod)
		+ info->concentration.extra;
    pf_printf("%s deals %d extra damage if the target is %s\n",
			info->name, result, info->concentration.targets[0]);
    return ;
}

int ft_check_buff_damage(SharedPtr<t_char> info)
{
    int r_value;

    r_value = 0;
    if (info->concentration.spell_id == HUNTERS_MARK_ID)
        ft_check_buff_damage_hunters_mark(info);
    return (r_value);
}
