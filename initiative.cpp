#include "dnd_tools.hpp"
#include <iostream>

void ft_check_initiative(t_char *info)
{
    if (info->initiative == -1)
        std::cout << "No initiative set for " << info->name << std::endl;
    else
        std::cout << info->name << " has an initiative roll of " << info->initiative << std::endl;
    return ;
}

void ft_roll_initiative(t_char *info)
{
    int dex_mod;
    int result;

    dex_mod = (info->stats.dex - 10) / 2;
    result = ft_dice_roll(1, 20);
    info->initiative = result + dex_mod;

    std::cout << info->name << " rolled " << result << "+" << dex_mod << "=" << info->initiative
              << " on his/her initiative" << std::endl;
    return ;
}
