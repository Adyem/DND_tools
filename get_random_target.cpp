#include "dnd_tools.hpp"

void	ft_get_random_target(const char **player_list, const char **target_field)
{
	int	i;

	i = ft_double_char_length(player_list);
	i = ft_dice_roll(1, i);
	*target_field = player_list[i];
	ft_remove_element(player_list, player_list[i]);
	return ;
}
