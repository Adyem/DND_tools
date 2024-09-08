#include "dnd_tools.hpp"
#include <iostream>

void ft_update_lightning_strike(t_char *info)
{
    int result;

    if (!info->bufs.lightning_strike.dice_amount ||
        !info->bufs.lightning_strike.dice_faces ||
        !info->bufs.lightning_strike.distance)
        return ;

    info->bufs.lightning_strike.duration--;

    if (info->bufs.lightning_strike.duration == 0)
    {
        result = ft_dice_roll(1, 8) + info->bufs.lightning_strike.extra_damage;
        std::cout << info->name << " his lightning strike markers explode dealing "
                  << result << " lightning damage to anyone standing within "
                  << info->bufs.lightning_strike.distance << " ft." << std::endl;
    }
    else if (info->bufs.lightning_strike.duration == 1)
        std::cout << info->name << " his lightning strike markers will explode on his next turn"
                  << std::endl;
    else
        std::cout << info->name << " his lightning strike markers will explode in "
                  << info->bufs.lightning_strike.duration << " turns" << std::endl;

    return ;
}
