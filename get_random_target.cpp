#include "dnd_tools.hpp"
#include "libft/RNG/RNG.hpp"

void    ft_get_random_target(char **player_list, char **target_field)
{
    int     length;

    length = ft_double_char_length(const_cast<const char **>(player_list));
    int index = ft_dice_roll(1, length) - 1;
    *target_field = player_list[index];
    ft_remove_element(player_list, player_list[index], false);
    return ;
}
