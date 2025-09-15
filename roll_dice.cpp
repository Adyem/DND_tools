#include "libft/Printf/printf.hpp"
#include "libft/RNG/rng.hpp"
#include "dnd_tools.hpp"
#include <climits>
#include <cstdlib>

void ft_reroll(t_char * info, int *result)
{
    int second_roll;

    if (DEBUG == 1)
        pf_printf_fd(2, "%s %d\n", info->name, *result);
    if (!info->flags.advantage)
        return ;
    second_roll = ft_dice_roll(1, 20);
    if (info->flags.advantage > 0)
    {
        pf_printf("%s rolled %d on his/her advantage\n", info->name, second_roll);
        if (second_roll > *result)
            *result = second_roll;
    }
    else if (info->flags.advantage < 0)
    {
        pf_printf("%s rolled %d on his/her disadvantage\n", info->name, second_roll);
        if (second_roll < *result)
            *result = second_roll;
    }
    return ;
}
