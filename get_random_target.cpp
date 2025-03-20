#include "dnd_tools.hpp"
#include "libft/RNG/dice_roll.hpp"

void	ft_get_random_target(char **player_list, char **target_field)
{
	int	i;

	i = ft_double_char_length(const_cast<const char **>(player_list));
	i = ft_dice_roll(1, i);
	*target_field = player_list[i];
	ft_remove_element(player_list, player_list[i], false);
	return ;
}
