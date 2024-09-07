#include "dnd_tools.hpp"
#include <iostream>

int ft_check_bless(t_char *info)
{
    int result;

    result = 0;
    if (info->bufs.bless.duration > 0)
        result += ft_dice_roll(1, 4);
    else
        return (0);
    std::cout << info->name << " rolled a " << result << " as an additional modifier for his/her bless buff" 
              << std::endl;
    return (result);
}
