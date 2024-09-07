#include "dnd_tools.hpp"
#include "identification.hpp"
#include <iostream>

static void ft_check_buff_damage_hunters_mark(t_char *info)
{
    int result;

    result = ft_dice_roll(1, 6);
    std::cout << info->name << " deals " << result << " extra damage if the target is " 
              << info->concentration.targets[0] << std::endl;
    return ;
}

int ft_check_buff_damage(t_char *info)
{
    int r_value;

    r_value = 0;
    if (info->concentration.spell_id == HUNTERS_MARK_ID)
        ft_check_buff_damage_hunters_mark(info);
    return (r_value);
}
