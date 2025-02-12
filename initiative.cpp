#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"

void ft_check_initiative(t_char * info)
{
    if (info->initiative == -1)
        pf_printf("No initiative set for %s\n", info->name);
    else
        pf_printf("%s has an initiative roll of %d\n", info->name, info->initiative);
    return ;
}

void ft_roll_initiative(t_char * info)
{
    int dex_mod;
    int result;

    dex_mod = (info->stats.dex - 10) / 2;
    result = ft_dice_roll(1, 20);
    info->initiative = result + dex_mod;
    pf_printf("%s rolled %d+%d=%d on his/her initiative\n",
			info->name, result, dex_mod, info->initiative);
    return ;
}
