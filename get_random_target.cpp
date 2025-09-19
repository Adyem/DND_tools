#include "dnd_tools.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/RNG/rng.hpp"

void    ft_get_random_target(ft_vector<ft_string> &player_list, char **target_field)
{
    int                             dice_faces;
    int                             index;
    ft_vector<ft_string>::iterator  it;

    if (!target_field || player_list.size() == 0)
        return ;
    dice_faces = static_cast<int>(player_list.size());
    index = ft_dice_roll(1, dice_faces) - 1;
    if (index < 0)
        return ;
    if (*target_field)
    {
        cma_free(*target_field);
        *target_field = ft_nullptr;
    }
    *target_field = cma_strdup(player_list[index].c_str());
    if (!*target_field)
    {
        player_list.clear();
        return ;
    }
    it = player_list.begin();
    it = it + index;
    player_list.erase(it);
    if (player_list.get_error() != ER_SUCCESS)
        player_list.clear();
    return ;
}
