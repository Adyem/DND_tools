#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

int ft_check_bless(ft_sharedptr<t_char> &info)
{
    int result;

    result = 0;
    if (info->bufs.bless.duration > 0)
        result += ft_dice_roll(1, 4);
    else
        return (0);
    pf_printf("%s rolled a %d as an additional modifier for his/her bless buff\n", info->name, result);
    return (result);
}

